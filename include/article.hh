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
    std::time_t publicationDate;
    std::string id;

public:
    Article(const std::string &title, const std::string &author, const std::string &text, const std::time_t publicationDate, const std::string id);
    const std::string &getTitle() const;
    const std::string &getAuthor() const;
    const std::string &getText() const;
    const std::time_t &getDate() const;
    const std::string &getId() const;
};

#endif
