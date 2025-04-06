#ifndef MEMDB_H
#define MEMDB_H
#include "database.h"
#include "article.h"
class Diskdb : public Database{
    private:

    public:
    Diskdb();
    ~Diskdb();
    void addNewsGroup(const Newsgroup&) override;
    void addArticle(Article* article,  Newsgroup& newsgroup)override;
    std::vector<Newsgroup > getNewsGroups() override;
    Article* getArticle(const std::string& newsgroup_id, const std::string &articleID) override;
    std::vector<Article*> getArticles(const std::string &groupId) override;
    bool deleteArticle(std::string &newsgroup, const std::string &articleId) override;
    bool removeNewsGroup(const std::string &groupId) override;

};

#endif