#include "commands.hh"
#include "database.hh"
#include "connection.hh"
#include "newsgroup.hh"
#include "message_handler.hh"
#include "utils.hh"
#include <iostream>

ListNG::ListNG(const std::vector<std::string> &string_tokinized)
{

    if (string_tokinized.size() != 2 || string_tokinized[0] != "COM_LIST_NG" || string_tokinized[1] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }
}

void ListNG::execute(Database &db, MessageHandler &messageHandler)
{
    // std::vector<Newsgroup> groups = db.getNewsGroups();

    // messageHandler.sendString("ANS_LIST_NG");

    // for (Newsgroup ng : groups)
    // {
    //     messageHandler.sendString(ng.getName());
    // }

    // messageHandler.sendString("ANS_END");
}

CreateNG::CreateNG(const std::vector<std::string> &string_tokinized)
{
    if (string_tokinized.size() != 5 || string_tokinized[0] != "COM_CREATE_NG" || string_tokinized[1] != "PAR_STRING" || !isDigit(string_tokinized[2]) || !isValidName(string_tokinized[3]) || string_tokinized[4] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }
    else
    {
        name = string_tokinized[1];
        id = string_tokinized[3];
    }
}

void CreateNG::execute(Database &db, MessageHandler &messageHandler)
{
}

DeleteNG::DeleteNG(const std::vector<std::string> &string_tokinized)
{
    if (string_tokinized.size() != 4 || string_tokinized[0] != "COM_DELETE_NG" || string_tokinized[1] != "PAR_NUM" || !isDigit(string_tokinized[2]) || string_tokinized[3] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }
    else
    {
        id = string_tokinized[3];
    }
}

void DeleteNG::execute(Database &db, MessageHandler &messageHandler)
{
    // db.removeNewsGroup(getNewsGroup());
}

Invalid::Invalid(const std::vector<std::string> &string_tokinized)
{
}

void Invalid::execute(Database &db, MessageHandler &messageHandler)
{
    // messageHandler.sendStringParameter("Invalid command bro\n");
}

ListArticles::ListArticles(const std::vector<std::string> &string_tokinized)
{
    if (string_tokinized.size() != 4 || string_tokinized[0] != "COM_LIST_ART" || string_tokinized[1] != "PAR_NUM" || !isDigit(string_tokinized[2]) || string_tokinized[3] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }
    else
    {
        group_id = string_tokinized[3];
    }
}

void ListArticles::execute(Database &db, MessageHandler &messageHandler)
{
    // std::vector<std::shared_ptr<Article>>  articles = db.getArticles();

    // messageHandler.sendString("ANS_LIST_ART ");

    // if(articles.empty()){
    //     messageHandler.sendString("ANS_NAK ERR_NG_DOES_NOT_EXIST");
    // } else{
    //     // for (Article article : articles)
    //     // {
    //     //     messageHandler.sendString(article.getTitle());
    //     // }
    // }

    // messageHandler.sendString("ANS_END");
}

CreateArticle::CreateArticle(const std::vector<std::string> &string_tokinized)
{

    int lastIndex = string_tokinized.size() - 1;

    if (string_tokinized.size() < 13 || string_tokinized[0] != "COM_CREATE_ART" || string_tokinized[1] != "PAR_NUM" || !isDigit(string_tokinized[2]) || string_tokinized[lastIndex] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }

    std::vector<size_t> indicies = findIndices(string_tokinized, "PAR_STRING");

    if (indicies.size() != 3)
    {

        throw std::invalid_argument("Invalid command format");
    }

    for (int i = 0; i < 3; i++)
    {
        int index_current_par_string = indicies[i];
        int index_next_par_string = i != 2 ? indicies[i + 1] : lastIndex;

        if (index_current_par_string == lastIndex || !isDigit(string_tokinized[index_current_par_string + 1]))
        {

            throw std::invalid_argument("Invalid command format");
        }
        else
        {
            int wordsExpected = std::stoi(string_tokinized[index_current_par_string + 1]);
            int words_actual = index_next_par_string - (index_current_par_string + 2);

            if (wordsExpected <= 0 || wordsExpected != words_actual)
            {
                throw std::invalid_argument("Invalid command format");
            }
        }
    }

    group_id = string_tokinized[2];
    title = joinStrings({string_tokinized.begin() + 5, string_tokinized.begin() + 5 + std::stoi(string_tokinized[indicies[0] + 1])}, " ");
    author = joinStrings({string_tokinized.begin() + indicies[1] + 2, string_tokinized.begin() + indicies[1] + 2 + std::stoi(string_tokinized[indicies[1] + 1])}, " ");
    text =  joinStrings({string_tokinized.begin() + indicies[2] + 2, string_tokinized.begin() + indicies[2] + 2 + std::stoi(string_tokinized[indicies[2] + 1])}, " ");
}

void CreateArticle::execute(Database &db, MessageHandler &messageHandler)
{
}

GetArticle::GetArticle(const std::vector<std::string> &string_tokinized)
{
    if (string_tokinized.size() != 6 || string_tokinized[0] != "COM_GET_ART" || string_tokinized[1] != "PAR_NUM" || !isDigit(string_tokinized[2]) || string_tokinized[3] != "PAR_NUM" || !isDigit(string_tokinized[4]) || string_tokinized[5] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }
    else
    {
        group_id = string_tokinized[2];
        article_id = string_tokinized[4];
    }
}

void GetArticle::execute(Database &db, MessageHandler &messageHandler)
{
}

DeleteArticle::DeleteArticle(const std::vector<std::string> &string_tokinized)
{
    if (string_tokinized.size() != 6 || string_tokinized[0] != "COM_DELETE_ART" || string_tokinized[1] != "PAR_NUM" || !isDigit(string_tokinized[2]) || string_tokinized[3] != "PAR_NUM" || !isDigit(string_tokinized[4]) || string_tokinized[5] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }
    else
    {
        group_id = string_tokinized[2];
        article_id = string_tokinized[4];
    }
}

void DeleteArticle::execute(Database &db, MessageHandler &messageHandler)
{
}
