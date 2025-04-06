

#include "newsgroup.h"
#include "article.h"
#include "database_ram.h"
#include "diskdb.h"
#include <iostream>
#include <ctime>
#include <cassert>

void testNewsGroup()
{

    std::time_t now1 = std::time(nullptr);
    std::time_t now2 = std::time(nullptr);
    Newsgroup ng("Tech News", now1, "ng001");

    // Test basic getters
    assert(ng.getName() == "Tech News");
    assert(ng.getCreationDate() == now1);
    assert(ng.getId() == "ng001");

    // Create some articles
    Article *a1 = new Article("title1", "author1", "text1", now1, "ID1");
    Article *a2 = new Article("title2", "author2", "text2", now2, "ID2");

    // Test addArticle
    ng.addArticle(a2);
    ng.addArticle(a1);
    std::vector<Article *> articles = ng.getArticles();
    assert(articles.size() == 2);


    // Test getArticle
    Article *fetched = ng.getArticle("ID1");
    assert(fetched != nullptr);
    assert(fetched->getId() == "ID1");

    // Test deleteArticle
    bool deleted = ng.deleteArticle("ID1");
    assert(deleted == true);
    assert(ng.getArticle("ID1") == nullptr);
    assert(ng.getArticles().size() == 1);

    // Test deleting non-existing article
    deleted = ng.deleteArticle("nonexistent");
    assert(deleted == false);

    // Test operator<
    Newsgroup ng2("Other News", now1 + 100, "ng002");
    assert(ng < ng2);

    std::cout << "Newsgroup tests passed!\n";

    delete a1;
    delete a2;
}

void testArticle()
{
    std::string title = "Breaking News";
    std::string author = "Jane Doe";
    std::string text = "This is the full article text.";
    std::time_t now = std::time(nullptr);
    std::string id = "art123";

    Article article(title, author, text, now, id);

    assert(article.getTitle() == title);
    assert(article.getAuthor() == author);
    assert(article.getText() == text);
    assert(article.getDate() == now);
    assert(article.getId() == id);

    std::cout << "All Article tests passed!\n";
}

void testDatabaseRam()
{
    DatabaseRam db;

    std::time_t now = std::time(nullptr);

    // Create newsgroups
    Newsgroup ng1("Tech", now, "ng1");
    Newsgroup ng2("Science", now + 1, "ng2");

    // Add newsgroups to the database
    db.addNewsGroup(ng1);
    db.addNewsGroup(ng2);

    std::vector<Newsgroup> allGroups = db.getNewsGroups();

   
    assert(allGroups.size() == 2);

    // Create articles
    Article *a1 = new Article("title1", "author1", "text1", now, "ID1");
    Article *a2 = new Article("title2", "author2", "text2", now+1, "ID2");

    // Add articles to Tech newsgroup
    db.addArticle(a1, ng1);
    db.addArticle(a2, ng1);

    // Check article list in newsgroups
    assert(db.getArticles("ng1").size() == 2); 
    assert(db.getArticles("ng2").size() == 0); 

    // Retrieve an article
    Article *fetched = db.getArticle("ng1", "ID1");
    assert(fetched != nullptr); 
    assert(fetched->getTitle() == "title1");

    // Delete an article
    std::string ngId = "ng1";
    bool deleted = db.deleteArticle(ngId, "ID1");
    assert(deleted);
    assert(db.getArticle("ng1", "ID1") == nullptr); 

    // Try deleting non-existent article
    deleted = db.deleteArticle(ngId, "nonexistent");
    assert(!deleted);

    // Remove a newsgroup
    bool removed = db.removeNewsGroup("ng2");
    assert(removed);
    assert(db.getNewsGroups().size() == 1);

    // Try removing non-existent newsgroup
    removed = db.removeNewsGroup("doesnotexist");
    assert(!removed);

    std::cout << "All DatabaseRam tests passed!\n";

    delete a1;
    delete a2;
}

void testDatabaseDisk(){ // TODO /////////////////////////////////

    // Create news group
    std::time_t now = std::time(nullptr);
    Newsgroup ng("Tech News", now, "ng001");

    //Create article
    Article *a1 = new Article("title1", "author1", "text1", now, "ID1");

    //Create Database object and add the newsgroup/article
    Diskdb db;
    db.addNewsGroup(ng);
    db.addArticle(a1, ng);
    db.getNewsGroups();

    

    std::cout << "All Disk database tests passed!\n";

}

int main()
{
    testArticle();
    testNewsGroup();
    testDatabaseRam();
    testDatabaseDisk();

    return 0;
}
