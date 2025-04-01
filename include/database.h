#ifndef DATABASE_H
#define DATABASE_H

#include "article.h"
#include <string.h>
#include<iostream>

class Database{

    virtual void addNewsGroup(const std::string&);
    virtual void addArticle(const Article&);

};

#endif