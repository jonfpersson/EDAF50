/* myclient.cc: sample client program */
#include "connection.hh"
#include "connectionclosedexception.hh"

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "message_handler.hh"
#include <memory>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
/*
 * Send an integer to the server as four bytes.
 */
void writeNumber(const Connection &conn, int value)
{
        conn.write((value >> 24) & 0xFF);
        conn.write((value >> 16) & 0xFF);
        conn.write((value >> 8) & 0xFF);
        conn.write(value & 0xFF);
}

/*
 * Read a string from the server.
 */
string readString(const Connection &conn)
{
        string s;
        char ch;
        while ((ch = conn.read()) != '$')
        {
                s += ch;
        }
        return s;
}

/* Creates a client for the given args, if possible.
 * Otherwise exits with error code.
 */
std::shared_ptr<Connection> init(int argc, char *argv[])
{
        if (argc != 3)
        {
                cerr << "Usage: myclient host-name port-number" << endl;
                exit(1);
        }

        int port = -1;
        try
        {
                port = std::stoi(argv[2]);
        }
        catch (std::exception &e)
        {
                cerr << "Wrong port number. " << e.what() << endl;
                exit(2);
        }
        auto conn = std::make_shared<Connection>(argv[1], port);

        if (!conn->isConnected())
        {
                cerr << "Connection attempt failed" << endl;
                exit(3);
        }

        return conn; // use this instead: &conn ?
}

void printMenu()
{
        std::vector<std::string> menu = {
            "-------------------------------------",
            "Welcome to the client program",
            "-------------------------------------",
            "Please choose an option:",
            "-------------------------------------",
            "1. List newsgroups",
            "2. Create newsgroup",
            "3. Delete newsgroup",
            "4. List articles",
            "5. Create article",
            "6. Delete article",
            "7. Get article",
            "8. Print menu",
            "9. Exit",
            "Choose an option (1-9):",
        };

        for (const auto &option : menu)
        {
                cout << option << endl;
        }
}

inline bool operator==(int value, Protocol protocol)
{
        return static_cast<int>(protocol) == value;
}

void list_newsgroups(MessageHandler &messageHandler)
{
        messageHandler.sendCode(Protocol::COM_LIST_NG);
        messageHandler.sendCode(Protocol::COM_END);

        messageHandler.recvCode();

        int nbrOfNewsgroups = messageHandler.recvIntParameter();

        cout << "______________Newsgroups______________" << endl;

        for (int i = 0; i < nbrOfNewsgroups; i++)
        {
                messageHandler.recvIntParameter();
                string newsgroup_title = messageHandler.recvStringParameter();
                cout << newsgroup_title << endl;
        }
        cout << "______________NewsgroupsEnd______________" << endl;
}

void create_newsgroup(MessageHandler &messageHandler)
{

        string newsgroupName;
        cout << "Enter the name of the newsgroup: ";
        cin >> newsgroupName;

        messageHandler.sendCode(Protocol::COM_CREATE_NG);
        messageHandler.sendStringParameter(newsgroupName);
        messageHandler.sendCode(Protocol::COM_END);

        // Wait for the server's response
        messageHandler.recvCode();

        int code = messageHandler.recvCode();

        if (code == Protocol::ANS_ACK)
        {
                cout << "Newsgroup created successfully." << endl;
        }
        else if (code == Protocol::ANS_NAK)
        {
                messageHandler.recvCode();
                cout << "Newsgroup already exists." << endl;
        }

        messageHandler.recvCode();
}

void delete_newsgroup(MessageHandler &messageHandler)
{
        int newsgroup_id;
        cout << "Enter the id of the newsgroup you wish to delete: " << endl;
        cin >> newsgroup_id;

        messageHandler.sendCode(Protocol::COM_DELETE_NG);
        messageHandler.sendIntParameter(newsgroup_id);
        messageHandler.sendCode(Protocol::COM_END);

        // wait for response

        messageHandler.recvCode();
        int code = messageHandler.recvCode();

        if (code == Protocol::ANS_ACK)
        {
        }
        else if (code == Protocol::ANS_NAK)
        {
                messageHandler.recvCode();
                cout << "Error: Newsgroup name exists... " << endl;
        }

        messageHandler.recvCode();
}

void list_articles(MessageHandler &messageHandler)
{
        string group_id;
        cout << "Enter the id of the group you wish to list the articles for: " << endl;
        cin >> group_id;

        // Await response

        messageHandler.recvCode();
        int code = messageHandler.recvCode();

        if (code == Protocol::ANS_ACK)
        {
                int nbrOfArticles = messageHandler.recvIntParameter();

                cout << "__________ARTICLES__________" << endl;
                for (int i = 0; i < nbrOfArticles; i++)
                {
                        int article_id = messageHandler.recvIntParameter();
                        string article_title = messageHandler.recvStringParameter();
                        cout << "Article id: " << article_id;
                        cout << "Article title: " << article_title;
                        cout << endl;
                }
                cout << "__________ARTICLES_END__________" << endl;
        }
        else if (code == Protocol::ANS_NAK)
        {
                messageHandler.recvCode();
                cout << "Newsgroup does not exist in this universe" << endl;
        }

        messageHandler.recvCode();
}

void create_article(MessageHandler &messageHandler)
{
        string title, author, text;
        int group_id;

        cout << "Enter the ID of the group in which you would like to add the article" << endl;
        cin >> group_id;

        cout << "Enter the title of the article:" << endl;
        cin >> title;

        cout << "Enter the name of the author:" << endl;
        cin >> author;

        cout << "Enter article text:" << endl;
        cin >> text;

        messageHandler.sendCode(Protocol::COM_CREATE_ART);
        messageHandler.sendIntParameter(group_id);
        messageHandler.sendStringParameter(title);
        messageHandler.sendStringParameter(author);
        messageHandler.sendStringParameter(text);
        messageHandler.sendCode(Protocol::COM_END);

        // Await response
        messageHandler.recvCode();
        int code = messageHandler.recvCode();

        if (code == Protocol::ANS_ACK)
        {
                cout << "Article created!" << endl;
        }
        else if (code == Protocol::ANS_NAK)
        {
                messageHandler.recvCode();
                cout << "Error: Newsgroup does not exist..." << endl;
        }

        messageHandler.recvCode();
}

void delete_article(MessageHandler &messageHandler)
{

        int group_id, article_id;

        cout << "Enter the ID of the group which contains the article you would like to delete:" << endl;
        cin >> group_id;

        cout << "Enter the ID of the article:" << endl;
        cin >> article_id;

        // Await response

        messageHandler.recvCode();
        int code = messageHandler.recvCode();
        if (code == Protocol::ANS_ACK)
        {
        }
        else if (code == Protocol::ANS_NAK)
        {
                int code = messageHandler.recvCode();

                string error = code == Protocol::ERR_NG_DOES_NOT_EXIST ? "Newsgroup does not exist" : "Article does not exist";

                cout << "Error:" << error << "..." << endl;
        }

        messageHandler.recvCode();
}

void get_article(MessageHandler &messageHandler)
{

        int group_id, article_id;

        cout << "Enter the ID of the group which contains the article you would like to get:" << endl;
        cin >> group_id;

        cout << "Enter the ID of the article:" << endl;
        cin >> article_id;

        messageHandler.sendCode(Protocol::COM_CREATE_ART);
        messageHandler.sendIntParameter(group_id);
        messageHandler.sendIntParameter(article_id);
        messageHandler.sendCode(Protocol::COM_END);

        // Await response

        messageHandler.recvCode();
        int code = messageHandler.recvCode();

        if (code == Protocol::ANS_ACK)
        {
                string title, author, text;
                title = messageHandler.recvStringParameter();
                author = messageHandler.recvStringParameter();
                text = messageHandler.recvStringParameter();
        }
        else if (code == Protocol::ANS_NAK)
        {
                int code = messageHandler.recvCode();

                string error = code == Protocol::ERR_NG_DOES_NOT_EXIST ? "Newsgroup does not exist" : "Article does not exist";

                cout << "Error:" << error << "..." << endl;
        }
        messageHandler.recvCode();
}

int app(MessageHandler &messageHandler)
{
        printMenu();
        int option;
        cin >> option;

        while (true)
        {
                switch (option)
                {
                case 1:
                        list_newsgroups(messageHandler);
                        break;
                case 2:
                        create_newsgroup(messageHandler);
                        break;
                case 3:
                        delete_newsgroup(messageHandler);
                        break;
                case 4:
                        list_articles(messageHandler);
                        break;
                case 5:
                        create_article(messageHandler);
                        break;
                case 6:
                        delete_article(messageHandler);
                        break;
                case 7:
                        get_article(messageHandler);
                        break;
                case 8:
                        printMenu();
                        break;
                case 9:
                        return 0;
                        break;
                default:
                        cout << "Invalid option. Please try again." << endl;
                        break;
                }

                cin >> option;
        }

        return 0;
}

int main(int argc, char *argv[])
{
        std::shared_ptr<Connection> conn = init(argc, argv);
        MessageHandler messageHandler{conn};

        return app(messageHandler);
}
