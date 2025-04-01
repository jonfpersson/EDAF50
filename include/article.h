#ifndef Article_H
#define Article_H

#include <string>
#include <iostream>

class Article
{
private:
    std::string title;
    std::string author;
    std::string text;
    std::string id;

public:
    Article(const std::string &title, const std::string &author, const std::string &text, const std::string id)
        : title{title}, author{author}, text{text}, id{id} {}

    const std::string& getTitle() const { return title; }
    const std::string& getAuthor() const { return author; }
    const std::string& getText() const { return text; }
    const std::string& getId() const { return id; }
};

#endif
