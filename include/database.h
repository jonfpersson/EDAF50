#ifndef DATABASE_H
#define DATABASE_H

#include "article.h"
#include <string.h>
#include <vector>
#include <iostream>
#include "newsgroup.h"

class Database
{
public:
    virtual ~Database() {}

    virtual void addNewsGroup(const Newsgroup &) = 0;
    virtual bool removeNewsGroup(const std::string &groupId) = 0;
    virtual std::vector<Newsgroup >& getNewsGroups() = 0; 

    virtual void addArticle(const Article &, const Newsgroup&) = 0;
    virtual Article &getArticle(const std::string &groupId, const std::string &articleId) = 0;
    virtual std::vector<Article >& getArticles(const std::string &groupId) = 0;
    virtual bool &deleteArticle(const std::string &groupId, const std::string &articleId) = 0;

};

#endif
