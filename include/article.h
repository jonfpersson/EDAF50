

#ifndef Article_H
#define Article_H

#include <string.h>
#include <iostream>

class Article
{
private:
    std::string& title;
    std::string& author;
    std::string& text;
    int id;

public:
    Article(std::string &title, std::string &author, std::string &text, int id) : title{title}, author{author}, text{text}, id{id}{}

    std::string& getTitle() const { return title; }
    std::string& getAuthor() const { return author; }
    std::string& getText() const { return text; }
    int getId() const { return id; }
};

#endif