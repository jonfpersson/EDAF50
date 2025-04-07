#ifndef MEMDB_H
#define MEMDB_H
#include "database.h"
#include "article.h"
class DatabaseDisk : public Database{
    private:

    public:
    DatabaseDisk();
    ~DatabaseDisk();
    void addNewsGroup(const Newsgroup&) override;
    void addArticle(std::shared_ptr<Article> article,  Newsgroup& newsgroup)override;
    std::vector<Newsgroup > getNewsGroups() override;
    std::shared_ptr<Article> getArticle(const std::string& newsgroup_id, const std::string &articleID) override;
    std::vector<std::shared_ptr<Article>> getArticles(const std::string &groupId) override;
    bool deleteArticle(std::string &newsgroup, const std::string &articleId) override;
    bool removeNewsGroup(const std::string &groupId) override;

};

#endif