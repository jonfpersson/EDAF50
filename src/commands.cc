#include "commands.hh"
#include "database.hh"
#include "connection.hh"
#include "newsgroup.hh"
#include "message_handler.hh"
#include "utils.hh"
#include <iostream>

ListNG::ListNG(const std::vector<std::string> &tokenized_string)
{

    if (tokenized_string.size() != 2 || tokenized_string[0] != "COM_LIST_NG" || tokenized_string[1] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }
}

void ListNG::execute(Database &db, MessageHandler &messageHandler)
{
    auto&& groups = db.getNewsGroups();

    messageHandler.sendCode(Protocol::ANS_LIST_NG);
    messageHandler.sendIntParameter(groups.size());

    for (auto it = groups.cbegin(); it != groups.cend(); ++it)
    {
        const Newsgroup &ng = *it;
        messageHandler.sendCode(Protocol::PAR_NUM);
        messageHandler.sendIntParameter(std::stoi(ng.getId()));
        messageHandler.sendCode(Protocol::PAR_STRING);
    }

    messageHandler.sendCode(Protocol::ANS_END);
}

CreateNG::CreateNG(const std::vector<std::string> &tokenized_string)
{
    if (tokenized_string.size() != 5 || tokenized_string[0] != "COM_CREATE_NG" || tokenized_string[1] != "PAR_STRING" || !isDigit(tokenized_string[2]) || !isValidName(tokenized_string[3]) || tokenized_string[4] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }
    else
    {
        name = tokenized_string[1];
        id = tokenized_string[3];
    }
}

void CreateNG::execute(Database &db, MessageHandler &messageHandler)
{
}

DeleteNG::DeleteNG(const std::vector<std::string> &tokenized_string)
{
    if (tokenized_string.size() != 4 || tokenized_string[0] != "COM_DELETE_NG" || tokenized_string[1] != "PAR_NUM" || !isDigit(tokenized_string[2]) || tokenized_string[3] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }
    else
    {
        id = tokenized_string[3];
    }
}

void DeleteNG::execute(Database &db, MessageHandler &messageHandler)
{
    // db.removeNewsGroup(getNewsGroup());
}

Invalid::Invalid(const std::vector<std::string> &tokenized_string)
{
}

void Invalid::execute(Database &db, MessageHandler &messageHandler)
{
    // messageHandler.sendStringParameter("Invalid command bro\n");
}

ListArticles::ListArticles(const std::vector<std::string> &tokenized_string)
{
    if (tokenized_string.size() != 4 || tokenized_string[0] != "COM_LIST_ART" || tokenized_string[1] != "PAR_NUM" || !isDigit(tokenized_string[2]) || tokenized_string[3] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }
    else
    {
        group_id = tokenized_string[3];
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

CreateArticle::CreateArticle(const std::vector<std::string> &tokenized_string)
{

    int lastIndex = tokenized_string.size() - 1;

    if (tokenized_string.size() < 13 || tokenized_string[0] != "COM_CREATE_ART" || tokenized_string[1] != "PAR_NUM" || !isDigit(tokenized_string[2]) || tokenized_string[lastIndex] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }

    std::vector<size_t> indicies = findIndices(tokenized_string, "PAR_STRING");

    if (indicies.size() != 3)
    {

        throw std::invalid_argument("Invalid command format");
    }

    for (int i = 0; i < 3; i++)
    {
        int index_current_par_string = indicies[i];
        int index_next_par_string = i != 2 ? indicies[i + 1] : lastIndex;

        if (index_current_par_string == lastIndex || !isDigit(tokenized_string[index_current_par_string + 1]))
        {

            throw std::invalid_argument("Invalid command format");
        }
        else
        {
            int wordsExpected = std::stoi(tokenized_string[index_current_par_string + 1]);
            int words_actual = index_next_par_string - (index_current_par_string + 2);

            if (wordsExpected <= 0 || wordsExpected != words_actual)
            {
                throw std::invalid_argument("Invalid command format");
            }
        }
    }

    group_id = tokenized_string[2];
    title = joinStrings({tokenized_string.begin() + 5, tokenized_string.begin() + 5 + std::stoi(tokenized_string[indicies[0] + 1])}, " ");
    author = joinStrings({tokenized_string.begin() + indicies[1] + 2, tokenized_string.begin() + indicies[1] + 2 + std::stoi(tokenized_string[indicies[1] + 1])}, " ");
    text =  joinStrings({tokenized_string.begin() + indicies[2] + 2, tokenized_string.begin() + indicies[2] + 2 + std::stoi(tokenized_string[indicies[2] + 1])}, " ");
}

void CreateArticle::execute(Database &db, MessageHandler &messageHandler)
{
}

GetArticle::GetArticle(const std::vector<std::string> &tokenized_string)
{
    if (tokenized_string.size() != 6 || tokenized_string[0] != "COM_GET_ART" || tokenized_string[1] != "PAR_NUM" || !isDigit(tokenized_string[2]) || tokenized_string[3] != "PAR_NUM" || !isDigit(tokenized_string[4]) || tokenized_string[5] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }
    else
    {
        group_id = tokenized_string[2];
        article_id = tokenized_string[4];
    }
}

void GetArticle::execute(Database &db, MessageHandler &messageHandler)
{
}

DeleteArticle::DeleteArticle(const std::vector<std::string> &tokenized_string)
{
    if (tokenized_string.size() != 6 || tokenized_string[0] != "COM_DELETE_ART" || tokenized_string[1] != "PAR_NUM" || !isDigit(tokenized_string[2]) || tokenized_string[3] != "PAR_NUM" || !isDigit(tokenized_string[4]) || tokenized_string[5] != "COM_END")
    {
        throw std::invalid_argument("Invalid command format");
    }
    else
    {
        group_id = tokenized_string[2];
        article_id = tokenized_string[4];
    }
}

void DeleteArticle::execute(Database &db, MessageHandler &messageHandler)
{
}
