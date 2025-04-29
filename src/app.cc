#include "newsgroup.hh"
#include "article.hh"
#include "database_ram.hh"
#include "database_disk.hh"
#include "server_handler.hh"
#include "command_parser.hh"
#include "commands.hh"
#include "database.hh"
#include "utils.hh"
#include <iostream>
#include <ctime>
#include <cassert>
#include<vector>
#include<string>

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
    std::shared_ptr<Article> a1 = std::make_shared<Article>("title1", "author1", "text1", now1, "ID1");
    std::shared_ptr<Article> a2 = std::make_shared<Article>("title2", "author2", "text2", now2, "ID2");

    // Test addArticle
    ng.addArticle(a2);
    ng.addArticle(a1);
    std::vector<std::shared_ptr<Article>> articles = ng.getArticles();
    assert(articles.size() == 2);

    // Test getArticle
    std::shared_ptr<Article> fetched = ng.getArticle("ID1");
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

void testDataBase(Database &db)
{
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
    std::shared_ptr<Article> a1 = std::make_shared<Article>("title1", "author1", "text1", now, "ID1");
    std::shared_ptr<Article> a2 = std::make_shared<Article>("title2", "author2", "text2", now + 1, "ID2");

    // Add articles to Tech newsgroup
    db.addArticle(a1, ng1);
    db.addArticle(a2, ng1);

    // Check article list in newsgroups
    assert(db.getArticles("ng1").size() == 2);
    assert(db.getArticles("ng2").size() == 0);

    // Retrieve an article
    std::shared_ptr<Article> fetched = db.getArticle("ng1", "ID1");
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
}

void testDatabaseRam()
{
    DatabaseRam db;
    testDataBase(db);
}

void testDatabaseDisk()
{

    DatabaseDisk db;
    testDataBase(db);
}

void testCommandParser()
{
    CommandParser parser;

    auto testParseCommand = [&](const std::string &commandStr, const std::type_info &expectedType)
    {
        std::unique_ptr<Command> command = parser.parse(commandStr);
        if(typeid(*command) != expectedType){
            std::cerr << "Failed to parse command: " << commandStr << std::endl;
            std::cerr << "Expected command type: " << expectedType.name() << ", but got: " << typeid(*command).name() << std::endl;
            exit(1);
        }
    };

    testParseCommand("COM_LIST_NG BEN DOVER COM_END", typeid(Invalid));
    testParseCommand("COM_LIST_NG COM_END", typeid(ListNG));
    testParseCommand("COM_CREATE_NG PAR_STRING 6 GROUP1 COM_END", typeid(CreateNG));
    testParseCommand("COM_CREATE_NG PAR_NUM 6 GROUP1 COM_END", typeid(Invalid));
    testParseCommand("COM_CREATE_NG PAR_STRING A GROUP1 COM_END", typeid(Invalid));
    testParseCommand("COM_DELETE_NG PAR_NUM 1 COM_END", typeid(DeleteNG));
    testParseCommand("COM_LIST_ART PAR_NUM 1 COM_END", typeid(ListArticles));
    testParseCommand("COM_CREATE_ART PAR_NUM 1 PAR_STRING 2 Deez nutz PAR_STRING 2 Ben Dover PAR_STRING 3 He asked me: COM_END", typeid(CreateArticle));
    testParseCommand("COM_CREATE_ART PAR_NUM 1 PAR_STRING 9 Deez nutz PAR_STRING 9 Ben Dover PAR_STRING 64 He asked me: \"what is ligma?\" and i deliviered the right answer. COM_END", typeid(Invalid));
    testParseCommand("COM_DELETE_ART PAR_NUM 1 PAR_NUM 1 COM_END", typeid(DeleteArticle));
    testParseCommand("COM_DELETE_ART PAR_STRING 1 PAR_NUM 1 COM_END", typeid(Invalid));

    std::cout << "Parse tests passed!\n";
}

int main()
{
    // testArticle();
    // testNewsGroup();
    // testDatabaseRam();
    // testDatabaseDisk();
    // testCommandParser();

    // serverHandler serv;
    // char *args[] = {"localhost", "8080"};
    // serv.setup(2, args);

    return 0;
}
