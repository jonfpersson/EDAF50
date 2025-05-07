#ifndef DATABASERAM_H
#define DATABASERAM_H

#include "article.hh"
#include "database.hh"
#include "newsgroup.hh"
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

class DatabaseRam : public Database
{

public:
    DatabaseRam();
    ~DatabaseRam();
    void addNewsGroup(const Newsgroup &) override;
    void addArticle(std::shared_ptr<Article> article, const Newsgroup& newsgroup) override;
    std::vector<Newsgroup> getNewsGroups() override;
    std::shared_ptr<Article> getArticle(const std::string& newsgroup_id, const std::string &articleID) override;
    std::vector<std::shared_ptr<Article>> getArticles(const std::string &groupIc) override;
    bool deleteArticle(std::string &newsgroup, const std::string &articleId) override;
    bool removeNewsGroup(const std::string &groupId) override;

private:
    std::vector<Newsgroup> newsgroups;
};

#endif