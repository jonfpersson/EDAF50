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
    std::string dir_name = newsgroup.getName() + " - " + newsgroup.getId();
    std::string file_name = article.getTitle() + " - " + std::to_string(article.getId());

    if(std::filesystem::exists(dir_name + "/" + file_name)){
        std::cout << "Article already exists!" << std::endl;
        return;
    }
    std::ofstream file(file_name);

    if (file.is_open()) {
        file << article.getAuthor() << std::endl;
        file << article.getText() << std::endl;
    
        file.close();
        //cout << "File created successfully." << endl;
    } else {
        std::cout << "Error in creating file!" << std::endl;
    }

}