#ifndef Article_H
#define Article_H

#include <string>
#include <iostream>
#include <ctime>

class Article
{
private:
    std::string title;
    std::string author;
    std::string text;
    std::string id;
    std::time_t publicationDate;

public:
    Article(const std::string &title, const std::string &author, const std::string &text, const std::time_t &publicationDate, const std::string id)
        : title{title}, author{author}, text{text}, publicationDate{publicationDate}, id{id} {}

    const std::string &getTitle() const { return title; }
    const std::string &getAuthor() const { return author; }
    const std::string &getText() const { return text; }
    const std::string &getId() const { return id; }
    const std::time_t &getDate() const { return publicationDate; }
};

#endif
