#ifndef DATABASE_H
#define DATABASE_H

#include "article.h"
#include <string.h>
#include <iostream>
#include "newsgroup.h"

class Database {
public:
    virtual ~Database() {}  
    
    virtual void addNewsGroup(const Newsgroup&) = 0;  
    virtual void addArticle(const Article&, const Newsgroup&) = 0;  
};

#endif
