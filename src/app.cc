#include "../include/diskdb.h"
#include "../include/newsgroup.h"
#include "../include/article.h"
#include "../include/database.h"
#include <iostream>

int main() {
    // Create a Newsgroup
    Newsgroup ng("Tech News", "001");

    // Create an Article
    Article art("AI Advances", "John Doe", "AI is changing the world!", 101);

    // Print Newsgroup details
    std::cout << "Newsgroup Created: " << ng.getName() << " (ID: " << ng.getId() << ")\n";

    // Print Article details
    std::cout << "Article Created:\n";
    std::cout << "Title: " << art.getTitle() << "\n";
    std::cout << "Author: " << art.getAuthor() << "\n";
    std::cout << "Text: " << art.getText() << "\n";
    std::cout << "ID: " << art.getId() << "\n";

    // Create Database object and add the newsgroup/article
    Diskdb db;
    db.addNewsGroup(ng);
    db.addArticle(art, ng);

    return 0;
}
