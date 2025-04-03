#include "../include/diskdb.h"
#include <filesystem>
#include <fstream>

Diskdb::Diskdb() {
}

Diskdb::~Diskdb() {
}

void Diskdb::addNewsGroup(const Newsgroup& newsgroup){
    std::string dir_name = newsgroup.getName() + " - " + newsgroup.getId();
   /* if(std::filesystem::exists(dir_name)){
        std::cout << "Newsgroup already exists!" << std::endl;
        return;
    }*/

    std::filesystem::create_directory(dir_name);

}

void Diskdb::addArticle(const Article& article, const Newsgroup& newsgroup){

    //format for a newgroup (directories)
    // name - id
    std::string test_dir = "test";
    std::string dir_name = test_dir + "/" +newsgroup.getName() + " - " + newsgroup.getId();
    std::string file_name = article.getTitle() + " - " + article.getId();

    if(std::filesystem::exists(dir_name + "/" + file_name)){
        std::cout << "Article already exists!" << std::endl;
        return;
    }
    std::ofstream file(dir_name + "/" +file_name);

    if (file.is_open()) {
        file << article.getAuthor() << std::endl;
        file << article.getText() << std::endl;
    
        file.close();
        //cout << "File created successfully." << endl;
    } else {
        std::cout << "Error in creating file!" << std::endl;
    }

}

std::vector<Newsgroup>& Diskdb::getNewsGroups() {
    static std::vector<Newsgroup> empty;
    return empty;
}

Article& Diskdb::getArticle(const std::string &groupId, const std::string &articleId) {
    static Article emptyArticle("", "", "", 0, ""); // placeholder
    return emptyArticle;
}

std::vector<Article>& Diskdb::getArticles(const std::string &groupId) {
    static std::vector<Article> emptyArticles; // placeholder
    return emptyArticles;
}

bool& Diskdb::deleteArticle(const std::string &groupId, const std::string &articleId) {
    static bool result = false; // placeholder
    return result;
}

bool Diskdb::removeNewsGroup(const std::string &groupId){
    return NULL;
}