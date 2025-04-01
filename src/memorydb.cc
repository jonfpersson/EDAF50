#include "memorydb.h"
#include <filesystem>

void MemoryDB::addNewsGroup(const std::string& name){
    std::filesystem::create_directory(name);

}

void MemoryDB::addArticle(const Article& article, const Newsgroup& newsgroup){
    std::cout << "addArticle" << std::endl;
    if(std::filesystem::exists(article.getTitle())){
        std::cout << "Article already exists!" << std::endl;
    }
}