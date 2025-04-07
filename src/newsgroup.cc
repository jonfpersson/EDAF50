
#include "newsgroup.h"
#include <article.h>


Newsgroup::Newsgroup(const std::string &name, const std::time_t creationDate, const std::string &id) : name{name}, creationDate{creationDate}, id{id} {}

const std::string &Newsgroup::getName() const { return name; }
const std::time_t &Newsgroup::getCreationDate() const { return creationDate; }
const std::string &Newsgroup::getId() const { return id; }

void Newsgroup::addArticle(std::shared_ptr<Article> article){
    articles.push_back(article);
}

std::vector<std::shared_ptr<Article>> Newsgroup::getArticles() const
{
    return articles;
}

bool Newsgroup::deleteArticle(const std::string &articleId)
{
    for (auto it = articles.begin(); it != articles.end(); ++it)
    {
        if ((*it)->getId() == articleId)
        {
            articles.erase(it);
            return true;
        }
    }
    return false;
}

std::shared_ptr<Article>Newsgroup::getArticle(const std::string &articleId) const
{
    for (auto it = articles.begin(); it != articles.end(); ++it)
    {
        if ((*it)->getId() == articleId)
        {
            return *it;
        }
    }
    return nullptr;
}


bool Newsgroup::operator<(const Newsgroup &other) const
{  
    if (creationDate != other.getCreationDate())
        return creationDate < other.getCreationDate();
    return id < other.getId();
}
