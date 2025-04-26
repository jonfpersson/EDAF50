#include "database_ram.hh"
#include "article.hh"
#include <string.h>
#include <iostream>
#include <memory>

DatabaseRam::DatabaseRam()
{
}

DatabaseRam::~DatabaseRam()
{
}

// handle if same groupe is added twice
void DatabaseRam::addNewsGroup(const Newsgroup &newsgroup)
{
    newsgroups.push_back(newsgroup);
}

// Handle error if the group does not exist!
void DatabaseRam::addArticle(std::shared_ptr<Article>article, const Newsgroup &newsgroup)
{

    for (auto it = newsgroups.begin(); it != newsgroups.end(); ++it)
    {
        if (it->getId() == newsgroup.getId())
        {
            it->addArticle(article);
        }
    }
};

std::vector<std::shared_ptr<Article>> DatabaseRam::getArticles(const std::string &groupId)
{

    for (auto it = newsgroups.begin(); it != newsgroups.end(); ++it)
    {
        if (it->getId() == groupId)
        {
            return it->getArticles();
        }
    }

    return std::vector<std::shared_ptr<Article>>();
}

std::vector<Newsgroup> DatabaseRam::getNewsGroups()
{
    return newsgroups;
};

std::shared_ptr<Article>DatabaseRam::getArticle(const std::string &newsgroupId, const std::string &articleID)
{

    for (auto nit = newsgroups.begin(); nit != newsgroups.end(); ++nit)
    {
        if (nit->getId() == newsgroupId)
        {
           
            for (std::shared_ptr<Article>a : nit->getArticles())
            {
                if (a->getId() == articleID)
                {     
                    return a;
                }
            }
        }
    }
    return nullptr;
};

bool DatabaseRam::deleteArticle(std::string &newsgroup, const std::string &articleId)
{

    for (auto nit = newsgroups.begin(); nit != newsgroups.end(); ++nit)
    {
        if (nit->getId() == newsgroup)
        {
            return nit->deleteArticle(articleId);
        }
    }

    return false;
};

bool DatabaseRam::removeNewsGroup(const std::string &groupId)
{

    for (auto nit = newsgroups.begin(); nit != newsgroups.end(); ++nit)
    {
        if (nit->getId() == groupId)
        {
            newsgroups.erase(nit);
            return true;
        }
    }

    return false;
};
