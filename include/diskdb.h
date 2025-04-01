#ifndef MEMDB_H
#define MEMDB_H
#include "database.h"
#include "article.h"
class Diskdb : Database{
    private:

    public:
    void addNewsGroup(const std::string&) override;
    void addArticle(const Article&, const Newsgroup&) override;

};

#endif