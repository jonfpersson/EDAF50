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
    void addArticle(const Article&, const Newsgroup&) override;
    std::vector<Newsgroup >& getNewsGroups() override;
    Article &getArticle(const std::string &groupId, const std::string &articleI) override;
    std::vector<Article >& getArticles(const std::string &groupI) override;
    bool &deleteArticle(const std::string &groupId, const std::string &articleI) override;
    bool removeNewsGroup(const std::string &groupId) override;

};

#endif