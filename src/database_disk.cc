#include "../include/database_disk.h"
#include <filesystem>
#include <fstream>
#include <istream>
static std::string test_dir = "test";

DatabaseDisk::DatabaseDisk() {
}

DatabaseDisk::~DatabaseDisk() {
}

void DatabaseDisk::addNewsGroup(const Newsgroup& newsgroup){
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

void DatabaseDisk::addArticle(std::shared_ptr<Article> article,  Newsgroup& newsgroup){

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

// detta returnerar egentligen en kopia av vectorn men men
std::vector<Newsgroup> DatabaseDisk::getNewsGroups() {
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


std::shared_ptr<Article> DatabaseDisk::getArticle(const std::string &groupId, const std::string &articleId) {
    for (auto const& files : std::filesystem::directory_iterator{test_dir + "/" + groupId}) {
        std::string title = files.path().filename();
        if(title.find("-") == std::string::npos || title.substr(title.find("-") + 2) != articleId){
            continue;
        }
        std::ifstream article_file(files.path());
        std::string author;
        getline(article_file, author);

        std::string text;
        getline(article_file, text);
        std::string id = title.substr(title.find("-") + 2);
        //get article name from file name
        title = title.substr(0, title.find("-") - 1);
        return std::make_shared<Article>(title, author, text, 0, id);
    }
    return nullptr;
}

std::vector<std::shared_ptr<Article>> DatabaseDisk::getArticles(const std::string &groupId) {
    std::vector<std::shared_ptr<Article>> articles;    
    for (auto const& files : std::filesystem::directory_iterator{test_dir + "/" + groupId}) {
        std::ifstream article_file(files.path());
        std::string author;
        getline(article_file, author);

        std::string text;
        getline(article_file, text);

        std::string title = files.path().filename();
        if(title.find("-") == std::string::npos){
            continue;
        }
        std::string id = title.substr(title.find("-") + 1);
        
        articles.push_back(std::make_shared<Article>(title, author, text, 0, id));

    }
        
    return articles;
}

bool DatabaseDisk::deleteArticle(std::string &newsgroup, const std::string &articleId){
    std::string dir_name = test_dir + "/" + newsgroup;
    for (auto const& files : std::filesystem::directory_iterator{dir_name}) {
        std::string title = files.path().filename();
        if(title.find("-") == std::string::npos || title.substr(title.find("-") + 2) != articleId){
            continue;
        }
        std::filesystem::remove(files.path());
        return true;
    }
    return false;
}

bool DatabaseDisk::removeNewsGroup(const std::string &groupId){
    std::string dir_name = test_dir + "/" + groupId;
    if(std::filesystem::exists(dir_name)){
        std::filesystem::remove_all(dir_name);
        return true;
    }
    return false;
}