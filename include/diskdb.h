#ifndef MEMDB_H
#define MEMDB_H
#include "database.h"
#include "article.h"
class Diskdb : public Database{
    private:

    public:
    void addNewsGroup(const Newsgroup&) override;
    void addArticle(const Article&, const Newsgroup&) override;

};

#endif