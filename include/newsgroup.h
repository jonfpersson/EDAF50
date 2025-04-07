

#ifndef newsgroup_H
#define newsgroup_H

#include <string.h>
#include <iostream>
#include <set>
#include "article.h"
#include <vector>
#include <memory>

class Newsgroup
{
private:
    std::string name;
    std::time_t creationDate;
    std::string id;
    std::vector<std::shared_ptr<Article>> articles;

public:
    Newsgroup(const std::string &name, const std::time_t creationDate, const std::string &id);

    bool operator<(const Newsgroup& other) const;
    const std::string& getName() const;
    const std::time_t& getCreationDate() const;
    const std::string& getId() const;
    void addArticle(std::shared_ptr<Article>);
    std::vector<std::shared_ptr<Article>> getArticles() const;
    std::shared_ptr<Article> getArticle(const std::string& articleId) const ;
    bool deleteArticle(const std::string& articleId);
};

#endif