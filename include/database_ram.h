#ifndef DATABASERAM_H
#define DATABASERAM_H

#include "article.h"
#include "database.h"
#include <string.h>
#include<iostream>
#include <unordered_map>
#include <vector>
#include "newsgroup.h"

class DatabaseRam : public Database {
    
    public:
        virtual void addNewsGroup(const Newsgroup&);
        virtual void addArticle(const Article&, const Newsgroup&);

    private:
        std::unordered_map<std::string, std::vector<const Article&>> newsgroups; //maps a newsgroup id to articles

};

#endif