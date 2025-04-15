#ifndef DATABASE_H
#define DATABASE_H

#include "article.hh"
#include "newsgroup.hh"
#include <string>
#include <vector>
#include <iostream>
#include <memory>

class Database
{
public:
    virtual ~Database() {}

    virtual void addNewsGroup(const Newsgroup &) = 0;
    virtual bool removeNewsGroup(const std::string &groupId) = 0;
    virtual  std::vector<Newsgroup> getNewsGroups()  = 0; 
    virtual  void addArticle(std::shared_ptr<Article> article,  Newsgroup& newsgroup)  = 0;
    virtual std::shared_ptr<Article> getArticle(const std::string& newsgroup_id, const std::string &articleID) = 0;
    virtual std::vector<std::shared_ptr<Article>> getArticles(const std::string &groupId) = 0;
    virtual bool deleteArticle(std::string &newsgroup, const std::string &articleId) = 0;
    

};

#endif
