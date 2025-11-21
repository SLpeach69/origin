#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/url/parse.hpp>
#include <boost/locale.hpp>
#include <regex>
#include <queue>
#include <unordered_set>
#include <queue>
#include <map>
#include <pqxx/pqxx>

using std::string;
using namespace boost::beast;
using namespace boost::asio;
struct INI {	
	string start_sayt;
	string path;
	string port;
	int recursiya;	
};

class Pauk {
private:
	std::chrono::steady_clock::time_point start_;
	std::chrono::steady_clock::time_point end;

	
	int recursiya;
	std::vector<std::thread> Pool_HTML;
	std::queue<std::function<void()>> Tasks_HTML;
	std::unordered_set<string> ref_HTML;
	int prev_ref_size_HTML = 0;
	std::mutex m_HTML;
	bool Stop_Pool_HTML = true;
	void Task_Load_HTML(string host, const string path, const string port, int recursiya);
	void Task_Load_BD(string html, string host, string path);
	string Load_HTML(const string host, const string path, const string port);
	std::pair<string, string> Razbor_Url_HTML(const string& url, string& Host);
	void Thread_Pool_Load_HTML();

	
	std::vector<std::thread> Pool_BD;
	std::queue<std::function<void()>> Tasks_BD;
	std::mutex m_BD;
	bool Stop_Pool_BD = true;
	pqxx::connection& bd;
	std::map<string, int> Html_v_Slova_v_Map(string& html, int min_slovo, int max_slovo);
	void Thread_Pool_Load_BD();

public:
	Pauk() = delete;
	Pauk(const Pauk&) = delete;
	Pauk(const Pauk&&) = delete;
	Pauk& operator=(const Pauk& other) = delete;
	Pauk& operator=(const Pauk&& other) = delete;
	Pauk(pqxx::connection& bd, const INI ini);
	~Pauk() {
		std::this_thread::sleep_for(std::chrono::seconds(recursiya*recursiya));
		Stop_Pool_HTML = false;
		for (auto& p : Pool_HTML)
			p.join();
		Stop_Pool_BD = false;
		for (auto& p : Pool_BD)
			p.join();
		end = chrono::steady_clock::now();
		std::cout << std::endl << "Vremya rabotyi Pauka sek: " << chrono::duration_cast<chrono::seconds>(end - start_).count() << std::endl;
	}
};
