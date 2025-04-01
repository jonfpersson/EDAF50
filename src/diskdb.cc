#include "diskdb.h"
#include <filesystem>

void Diskdb::addNewsGroup(const std::string& name){
    std::filesystem::create_directory(name);

}

void Diskdb::addArticle(const Article& article, const Newsgroup& newsgroup){
    std::cout << "addArticle" << std::endl;
    if(std::filesystem::exists(article.getTitle())){
        std::cout << "Article already exists!" << std::endl;
    }
}