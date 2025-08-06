#include <string>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};


class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }

};
class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        string original = data;

        reverse(original.begin(), original.end());
        text_->render(original);
                

    }

};
class Link :public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render( const std::string& add, const std::string& data) const {
        
        std::cout << "<a href="<< add<< ">";
       
        text_->render(data);
        std::cout << "</a>";

    }


};

int main_2() {
 
    auto text_block1 = new Paragraph(new Text());
    text_block1->render("Hello world");
    cout << endl;
    auto text_block2 = new Reversed (new Text());
    text_block2->render("Hello world");
    cout << endl;
    auto text_block3 = new Link(new Text());
    text_block3->render("netology.ru", "Hello world");
    return 0;
}