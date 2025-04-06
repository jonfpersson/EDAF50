#include "../include/diskdb.h"
#include <filesystem>
#include <fstream>
#include <istream>
static std::string test_dir = "test";

Diskdb::Diskdb() {
}

Diskdb::~Diskdb() {
}

void Diskdb::addNewsGroup(const Newsgroup& newsgroup){
    std::string test_dir = "test";
    std::filesystem::create_directory(test_dir);
    std::string dir_name = test_dir + "/" + newsgroup.getId();
   /* if(std::filesystem::exists(dir_name)){
        std::cout << "Newsgroup already exists!" << std::endl;
        return;
    }*/

    std::filesystem::create_directory(dir_name);

    std::string file_metadata = "metadata";
    std::ofstream file(dir_name + "/" + file_metadata);
    if (file.is_open()) {
        file << newsgroup.getCreationDate() << std::endl;
        file << newsgroup.getName() << std::endl;
    
        file.close();
        //cout << "File created successfully." << endl;
    } else {
        std::cout << "Error in creating file!" << std::endl;
    }


}

void Diskdb::addArticle(Article* article,  Newsgroup& newsgroup){

    //format for a newgroup (directories)
    // name - id
    std::string dir_name = test_dir + "/" + newsgroup.getId();
    std::string file_name = article->getTitle() + " - " + article->getId();

    if(std::filesystem::exists(dir_name + "/" + file_name)){
        std::cout << "Article already exists!" << std::endl;
        return;
    }
    std::ofstream file(dir_name + "/" +file_name);

    if (file.is_open()) {
        file << article->getAuthor() << std::endl;
        file << article->getText() << std::endl;
    
        file.close();
        //cout << "File created successfully." << endl;
    } else {
        std::cout << "Error in creating file!" << std::endl;
    }

}

std::vector<Newsgroup> Diskdb::getNewsGroups() {
    std::vector<Newsgroup> groups;    
    for (auto const& dir_entry : std::filesystem::directory_iterator{test_dir}) {
        std::ifstream metadata_file(dir_entry.path() / "metadata");
        std::string creationDate;
        getline(metadata_file, creationDate);

        std::string name;
        getline(metadata_file, name);

        groups.push_back(Newsgroup(dir_entry.path().filename(), std::stoi(creationDate), name));
    }

    return groups; 
}


Article* Diskdb::getArticle(const std::string &groupId, const std::string &articleId) {
    static Article emptyArticle("", "", "", 0, ""); // placeholder
    return nullptr;
}

std::vector<Article*> Diskdb::getArticles(const std::string &groupId) {
    static std::vector<Article*> emptyArticles; // placeholder
    return emptyArticles ;
}

bool Diskdb::deleteArticle(std::string &newsgroup, const std::string &articleId){
    static bool result = false; // placeholder
    return result;
}

bool Diskdb::removeNewsGroup(const std::string &groupId){
    return false;
}