#include "database_ram.h"
#include "article.h"
#include <string.h>
#include <iostream>

void DatabaseRam::addNewsGroup(const Newsgroup& newsgroup)
{
    DatabaseRam::newsgroups[newsgroup.getId()];
}

DatabaseRam::DatabaseRam(){ 
}

// Handle error if the group does not exist!
void DatabaseRam::addArticle(const Article &article, const Newsgroup &newsgroup)
{
    DatabaseRam::newsgroups.at(newsgroup.getId()).push_back(article);
}