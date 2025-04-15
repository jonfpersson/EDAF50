
#include "article.hh"

#include <string>
#include <iostream>
#include <ctime>


Article::Article(const std::string &title, const std::string &author, const std::string &text, const std::time_t publicationDate, const std::string id)
    : title{title}, author{author}, text{text}, publicationDate{publicationDate}, id{id} {}

const std::string &Article::getTitle() const { return title; }

const std::string &Article::getAuthor() const { return author; }
const std::string &Article::getText() const { return text; }
const std::time_t &Article::getDate() const { return publicationDate; }
const std::string &Article::getId() const { return id; }
