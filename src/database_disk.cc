#include "database_disk.hh"
#include <filesystem>
#include <fstream>
#include <istream>
#include <algorithm>
#include <cctype>
#include <string>
#include "connectionclosedexception.hh"

static std::string test_dir = "database_files";

DatabaseDisk::DatabaseDisk() {
    std::filesystem::create_directory(test_dir);
}

DatabaseDisk::~DatabaseDisk() {
}

void DatabaseDisk::addNewsGroup(const Newsgroup& newsgroup){
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

void DatabaseDisk::addArticle(std::shared_ptr<Article> article, const Newsgroup& newsgroup){

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
        file << article->getDate() << std::endl;
        file << article->getText();

        file.close();
        //cout << "File created successfully." << endl;
    } else {
        std::cout << "Error in creating file!" << std::endl;
    }

}

// detta returnerar egentligen en kopia av vectorn men men
#include <algorithm> // for std::sort

std::vector<Newsgroup> DatabaseDisk::getNewsGroups() {
    std::vector<Newsgroup> groups;

    for (const auto& dir_entry : std::filesystem::directory_iterator{test_dir}) {
        if (!dir_entry.is_directory()) {
            continue;
        }

        auto metadata_path = dir_entry.path() / "metadata";
        if (!std::filesystem::exists(metadata_path)) {
            continue;
        }

        std::ifstream metadata_file(metadata_path);
        if (!metadata_file.is_open()) {
            continue;
        }

        std::string creationDateStr;
        std::getline(metadata_file, creationDateStr);

        std::string name;
        std::getline(metadata_file, name);

        if (!creationDateStr.empty() && !name.empty()) {
            int creationDate = std::stoll(creationDateStr);
            groups.emplace_back(name, creationDate, dir_entry.path().filename());
        }
    }

    // Sort by creationDate (assuming it's an int and the second parameter in Newsgroup)
    std::sort(groups.begin(), groups.end(), [](const Newsgroup& a, const Newsgroup& b) {
        return a.getCreationDate() < b.getCreationDate(); // Replace with your actual accessor
    });

    return groups;
}



inline std::string trim(const std::string& s) {
    // Trim only spaces and tabs, not newlines
    auto start = std::find_if_not(s.begin(), s.end(),
                                  [](unsigned char c) { return c == ' ' || c == '\t'; });
    auto end = std::find_if_not(s.rbegin(), s.rend(),
                                [](unsigned char c) { return c == ' ' || c == '\t'; }).base();

    if (start >= end)
        return "";

    return std::string(start, end);
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
        std::string date;
        std::getline(article_file, date);

        std::string text((std::istreambuf_iterator<char>(article_file)),
        std::istreambuf_iterator<char>());
        std::string id = title.substr(title.find("-") + 2);
        title = title.substr(0, title.find("-") - 1);

        return std::make_shared<Article>(title, author, trim(text), std::stoll(date), id);
    }
    return nullptr;
}

std::vector<std::shared_ptr<Article>> DatabaseDisk::getArticles(const std::string &groupId) {
    std::vector<std::shared_ptr<Article>> articles;

    
    if (!std::filesystem::exists(test_dir + "/" + groupId)) {
        return articles;
        std::cout << "No such group exists" << std::endl;
    }
    
    for (const auto& files : std::filesystem::directory_iterator{test_dir + "/" + groupId}) {
        std::ifstream article_file(files.path());
        if (!article_file.is_open()) continue;

        std::string author;
        std::getline(article_file, author);

        std::string date;
        std::getline(article_file, date);

        std::string text((std::istreambuf_iterator<char>(article_file)),
                         std::istreambuf_iterator<char>());

        std::string title = files.path().filename();
        if (title.find("-") == std::string::npos) {
            continue;
        }

        std::string id = title.substr(title.find("-") + 2);
        title = title.substr(0, title.find("-") - 1);

        articles.push_back(std::make_shared<Article>(title, author, trim(text), std::stoll(date), id));
    }

    // Sort articles by date (assumed to be a member of Article)
    std::sort(articles.begin(), articles.end(), [](const auto& a, const auto& b) {
        return a->getDate() < b->getDate();  // Replace getDate() with the correct accessor if different
    });

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