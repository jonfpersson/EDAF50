#ifndef DATABASE_H
#define DATABASE_H

#include "article.h"
#include <string.h>
#include <iostream>
#include "newsgroup.h"

class Database{

    virtual void addNewsGroup(const std::string&);
    virtual void addArticle(const Article&, const Newsgroup&);

};

#endif