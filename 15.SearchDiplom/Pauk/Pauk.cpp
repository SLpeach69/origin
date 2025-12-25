#include "Pauk.h"

Pauk::Pauk(pqxx::connection& bd, const INI ini) : bd(bd), recursiya(ini.recursiya) {
    start_ = chrono::steady_clock::now();

    pqxx::work w{ bd };
    w.exec("create table if not exists ref(id serial PRIMARY KEY not null,host varchar ,path varchar )");
    w.exec("create table if not exists data(id serial not null, nomer_ref int  references ref (id)  not null, slovo varchar ,size int )");
    w.commit();

    boost::locale::generator gen;
    std::locale loc = gen.generate("");
    std::locale::global(loc);
    std::wcout.imbue(loc);

    Tasks_HTML.push([ini, this]() { Task_Load_HTML(ini.start_sayt, ini.path, ini.port, recursiya); });

    for (int i = 0; i < std::thread::hardware_concurrency() / 2; ++i) {
        Pool_HTML.emplace_back(&Pauk::Thread_Pool_Load_HTML, this);
        Pool_BD.emplace_back(&Pauk::Thread_Pool_Load_BD, this);
    }
}


void Pauk::Task_Load_HTML(string host, string path, const string port, int recursiya) {
    const string html = Load_HTML(host, path, port);
    if (html.empty())
        return;

    m_HTML.lock();
    Tasks_BD.push([html, host, path, this]() {Pauk::Task_Load_BD(html, host, path); });
    static int x = 0;
    std::cout << "Kolvo_Saytov  " << ++x << "  ID Potoka  " << std::this_thread::get_id() << "  Tasks  " << Tasks_HTML.size() << std::endl;
    m_HTML.unlock();

    if (--recursiya == 0)
        return;
    std::smatch match;
    std::string::const_iterator Html_Start(html.cbegin());
    while (std::regex_search(Html_Start, html.cend(), match, std::regex("<a href=\"(.*?)\""))) {
        auto [Host, Path] = Razbor_Url_HTML(match[1], host);
        Html_Start = match.suffix().first;
        m_HTML.lock();
        ref_HTML.insert(Host + Path);
        int size = ref_HTML.size();
        int prev = prev_ref_size_HTML;
        m_HTML.unlock();
        if (prev == size)
            continue;
        m_HTML.lock();
        prev_ref_size_HTML = size;
        Tasks_HTML.push([Host, Path, port, recursiya, this]() {Pauk::Task_Load_HTML(Host, Path, port, recursiya); });
        m_HTML.unlock();
    }
}


string Pauk::Load_HTML(const string host, const string path, const string port) {
    string current_host = host;
    string current_path = path;
    const int max_redirects = 5;
    int redirect_count = 0;

    while (redirect_count <= max_redirects) {
        string html;
        try {
            io_service servis;
            ssl::context context(ssl::context::tls_client);
            context.set_default_verify_paths();
            ssl::stream<ip::tcp::socket> ssocket(servis, context);
            ssocket.set_verify_mode(ssl::verify_none);

            ip::tcp::resolver resolver(servis);
            auto it = resolver.resolve(current_host, port);

            connect(ssocket.lowest_layer(), it);
            ssocket.lowest_layer().set_option(ip::tcp::no_delay(true));

            if (!SSL_set_tlsext_host_name(ssocket.native_handle(), current_host.c_str())) {
                boost::system::error_code ec{ static_cast<int>(::ERR_get_error()),
                    boost::asio::error::get_ssl_category() };
                throw boost::system::system_error{ ec };
            }

            ssocket.handshake(ssl::stream_base::handshake_type::client);

            http::request<http::string_body> req{ http::verb::get, current_path, 11 };
            req.set(http::field::host, current_host);
            req.set(http::field::user_agent, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36");
            req.set(http::field::accept, "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
            req.set(http::field::accept_language, "en-US,en;q=0.9,ru;q=0.8");
            req.set(http::field::connection, "keep-alive");

            m_HTML.lock();
            http::write(ssocket, req);
            m_HTML.unlock();

            http::response<http::string_body> res;
            flat_buffer buffer;
            http::read(ssocket, buffer, res);
            html = res.body().data();

            if (res.result() >= http::status::moved_permanently &&
                res.result() <= http::status::permanent_redirect) {

                auto [new_host, new_path] = HandleRedirect(res, current_host, current_path);

                if (new_host != current_host || new_path != current_path) {
                    current_host = new_host;
                    current_path = new_path;
                    redirect_count++;
                    continue;
                }
            }

            return html;
        }
        catch (const std::exception& e) {
            std::cerr << "Error loading HTML from " << current_host << current_path
                << ": " << e.what() << std::endl;
            return "";
        }
    }

    std::cerr << "Too many redirects for " << host << path << std::endl;
    return "";
}


std::pair<string, string> Pauk::Razbor_Url_HTML(const string& url, string& Host) {
    string host, path;
    try {
        boost::urls::url_view URL(url);
        host = URL.host();
        path = URL.path();
        if (host.empty())
            host = Host;
        else
            Host = host;
        if (path.empty())
            path = "/";
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing URL: " << url << " - " << e.what() << std::endl;
    }
    return std::make_pair(host, path);
}


void Pauk::Thread_Pool_Load_HTML() {
    while (Stop_Pool_HTML || !Tasks_HTML.empty()) {
        int x = Tasks_HTML.size();
        if (x < 10)
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 5 * 100));
        m_HTML.lock();
        if (!Tasks_HTML.empty()) {
            auto task = Tasks_HTML.front();
            Tasks_HTML.pop();
            m_HTML.unlock();
            task();
        }
        else {
            m_HTML.unlock();
        }
    }
}



void Pauk::Task_Load_BD(string html, string host, string path) {
    static int count = 0;
    try {
        auto slova = Html_v_Slova_v_Map(html, 3, 15);
        m_BD.lock();
        ++count;
        std::cout << "Kolvo_load  " << count << "  ID Potoka  " << std::this_thread::get_id() << "  Tasks_BD  " << Tasks_BD.size() << std::endl;
        pqxx::work w{ bd };
        w.exec("insert into ref(host, path) values ('" + host + "', '" + path + "')");
        for (auto [key, size] : slova) {
            w.exec("insert into data(nomer_ref, slovo, size) values (" + std::to_string(count) + ", '" + key + "', " + std::to_string(size) + ")");
        }
        w.commit();
        m_BD.unlock();
    }
    catch (const std::exception& e) {
        m_BD.unlock();
        std::cerr << "Error in Task_Load_BD: " << e.what() << std::endl;
        --count;
    }
}


std::map<string, int> Pauk::Html_v_Slova_v_Map(string& html, int min_slovo, int max_slovo) {
    bool trigger = false;
    for (int i = 0; i < html.size(); ++i) {
        if (html[i] == '<')
            trigger = true;
        if (html[i] == '>')
            trigger = false;
        if (trigger) {
            html.erase(i, 1); --i;
        }
    }

    for (int i = 0; i < html.size(); ++i) {
        unsigned char z = html[i];
        if (z < 32 || (z > 32 && z < 65) || (z > 90 && z < 97) || (z > 122 && z < 128)) {
            html[i] = ' ';
        }
    }

    for (int i = 0; i < html.size() - 1; ++i) {
        if (html[i] == ' ' && html[i + 1] == ' ') {
            html.erase(i, 1);
            --i;
        }
    }

    if (html[0] == ' ')
        html.erase(0, 1);

    html = boost::locale::to_lower(html);

    std::map<string, int>map;
    string temp;
    for (auto& x : html) {
        int temp_min, temp_max;
        if (x != ' ') {
            temp += x;
        }
        else {
            if (unsigned(temp[0]) >= 208) {
                temp_min = min_slovo * 2;
                temp_max = max_slovo * 2;
            }
            else {
                temp_min = min_slovo;
                temp_max = max_slovo;
            }
            if (temp.size() <= temp_min) {
                temp = ""; continue;
            }
            if (temp.size() > temp_max) {
                temp = ""; continue;
            }

            map[temp]++;
            temp = "";
        }
    };
    return map;
};

void Pauk::Thread_Pool_Load_BD() {
    while (Stop_Pool_BD || !Tasks_BD.empty()) {
        int x = Tasks_BD.size();
        if (x < 20)
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 5 * 100));
        m_BD.lock();
        if (!Tasks_BD.empty()) {
            auto task = Tasks_BD.front();
            Tasks_BD.pop();
            m_BD.unlock();
            task();
        }
        else {
            m_BD.unlock();
        }
    }
}

std::pair<string, string> Pauk::HandleRedirect(const http::response<http::string_body>& response,
    const string& current_host, const string& current_path) {

    if (response.result() >= http::status::moved_permanently &&
        response.result() <= http::status::permanent_redirect) {

        auto location_header = response.find(http::field::location);
        if (location_header != response.end()) {
            string redirect_url = location_header->value().to_string();

            try {
                boost::urls::url_view url_view(redirect_url);

                string new_host = url_view.has_host() ?
                    url_view.host() : current_host;

                string new_path = url_view.has_path() ?
                    url_view.path() : "/";

                if (redirect_url.find("http") != 0) {
                    if (redirect_url[0] == '/') {
                        return { current_host, redirect_url };
                    }
                    else {
                        string full_path = current_path;
                        if (full_path.back() != '/') {
                            size_t last_slash = full_path.find_last_of('/');
                            if (last_slash != string::npos) {
                                full_path = full_path.substr(0, last_slash + 1);
                            }
                        }
                        full_path += redirect_url;
                        return { current_host, full_path };
                    }
                }

                return { new_host, new_path };
            }
            catch (const std::exception& e) {
                std::cerr << "Error parsing redirect URL: " << redirect_url << " - " << e.what() << std::endl;
            }
        }
    }
    return { current_host, current_path };
}
