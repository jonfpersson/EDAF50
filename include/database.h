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
    virtual  std::vector<Newsgroup> getNewsGroups()  = 0; 
    virtual  void addArticle(Article* article,  Newsgroup& newsgroup)  = 0;
    virtual Article* getArticle(const std::string& newsgroup_id, const std::string &articleID) = 0;
    virtual std::vector<Article*> getArticles(const std::string &groupId) = 0;
    virtual bool deleteArticle(std::string &newsgroup, const std::string &articleId) = 0;
    

};

#endif
