#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

class Text {
public:
    virtual std::string render(const std::string& text) const {
        return text;
    }

    virtual ~Text() = default;
};

class Paragraph : public Text {
private:
    std::unique_ptr<Text> text;

public:
    Paragraph(Text* text) : text(text) {}

    std::string render(const std::string& content) const override {
        return "<p>" + text->render(content) + "</p>";
    }
};

class Reversed : public Text {
private:
    std::unique_ptr<Text> text;

public:
    Reversed(Text* text) : text(text) {}

    std::string render(const std::string& content) const override {
        std::string reversed_content = content;
        std::reverse(reversed_content.begin(), reversed_content.end());
        return text->render(reversed_content);
    }
};

class Link : public Text {
private:
    std::unique_ptr<Text> text;

public:
    Link(Text* text) : text(text) {}

    std::string render(const std::string& url, const std::string& content) const {
        return "<a href=" + url + ">" + text->render(content) + "</a>";
    }

    std::string render(const std::string& content) const override {
        return render("", content);
    }
};

int main() {
    auto paragraph = std::make_unique<Paragraph>(new Text());
    std::cout << paragraph->render("Hello world") << std::endl;

    auto reversed = std::make_unique<Reversed>(new Text());
    std::cout << reversed->render("Hello world") << std::endl;

    auto link = std::make_unique<Link>(new Text());
    std::cout << link->render("netology.ru", "Hello world") << std::endl;

    auto reversed_paragraph = std::make_unique<Reversed>(new Paragraph(new Text()));
    std::cout << reversed_paragraph->render("Hello world") << std::endl;

    auto linked_reversed = std::make_unique<Link>(new Reversed(new Text()));
    std::cout << linked_reversed->render("netology.ru", "Hello world") << std::endl;

    return 0;
}