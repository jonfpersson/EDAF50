#include "commands.hh"
#include "database.hh"
#include "connection.hh"
#include "newsgroup.hh"
#include "message_handler.hh"
#include "utils.hh"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <cstdint>

int readNumber(const std::vector<Protocol> &tokenized_string, int startindex)
{
        int byte1 = static_cast<int>(tokenized_string[startindex++]);
        int byte2 = static_cast<int>(tokenized_string[startindex++]);
        int byte3 = static_cast<int>(tokenized_string[startindex++]);
        int byte4 = static_cast<int>(tokenized_string[startindex]);
        std::cout << "bytes:" << byte2 << " " << byte2 << " " << byte3 << " " << byte4 << std::endl;
        return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

ListNG::ListNG(const std::vector<Protocol> &tokenized_string)
{

}

void ListNG::execute(Database &db, MessageHandler &messageHandler)
{
    auto&& groups = db.getNewsGroups();

    messageHandler.sendCode(Protocol::ANS_LIST_NG);
    messageHandler.sendIntParameter(groups.size());

    for (auto it = groups.cbegin(); it != groups.cend(); ++it)
    {
        const Newsgroup &ng = *it;
        messageHandler.sendIntParameter(std::stoi(ng.getId()));
        messageHandler.sendStringParameter((ng.getName()));

    }

    messageHandler.sendCode(Protocol::ANS_END);
}

CreateNG::CreateNG(const std::vector<Protocol> &tokenized_string) {

    size_t i = 0;

    if (tokenized_string[i++] != Protocol::COM_CREATE_NG) {
        throw std::invalid_argument("Expected COM_CREATE_NG");
    }

    if (tokenized_string[i++] != Protocol::PAR_STRING) {
        throw std::invalid_argument("Expected PAR_STRING");
    }
    i++; //????
    i++;
    i++;

    int str_len = static_cast<int>(tokenized_string[i++]);


    std::string extracted_name;
    for (int j = 0; j < str_len; ++j) {
        extracted_name += static_cast<char>(static_cast<int>(tokenized_string[i++]));
    }

    name = extracted_name;

}

void CreateNG::execute(Database &db, MessageHandler &messageHandler)
{
    messageHandler.sendCode(Protocol::ANS_CREATE_NG);
    auto&& groups = db.getNewsGroups();
    for(auto it = groups.cbegin(); it != groups.cend(); ++it)
    {
        const Newsgroup &ng = *it;
        if(ng.getName() == name)
        {
            messageHandler.sendCode(Protocol::ANS_NAK);
            messageHandler.sendCode(Protocol::ERR_NG_ALREADY_EXISTS);
            messageHandler.sendCode(Protocol::ANS_END);
            return;
        }
    }
    messageHandler.sendCode(Protocol::ANS_ACK);

    db.addNewsGroup(Newsgroup(name, std::time(nullptr), std::to_string(random_number)));
    messageHandler.sendCode(Protocol::ANS_END);

}

DeleteNG::DeleteNG(const std::vector<Protocol> &tokenized_string) {

    id = std::to_string(readNumber(tokenized_string, 2));
}

void DeleteNG::execute(Database &db, MessageHandler &messageHandler)
{
    messageHandler.sendCode(Protocol::ANS_DELETE_NG);
    auto&& groups = db.getNewsGroups();
    for(auto it = groups.cbegin(); it != groups.cend(); ++it)
    {
        const Newsgroup &ng = *it;
        if(ng.getId() == id)
        {
            db.removeNewsGroup(id);
            messageHandler.sendCode(Protocol::ANS_ACK);
            messageHandler.sendCode(Protocol::ANS_END);
            return;
        }
    }
    messageHandler.sendCode(Protocol::ANS_NAK);
    messageHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
    messageHandler.sendCode(Protocol::ANS_END);

}

Invalid::Invalid(const std::vector<Protocol> &tokenized_string)
{
}

void Invalid::execute(Database &db, MessageHandler &messageHandler)
{
    // messageHandler.sendStringParameter("Invalid command bro\n");
}

ListArticles::ListArticles(const std::vector<Protocol> &tokenized_string) {
    group_id = std::to_string(readNumber(tokenized_string, 2));
}

void ListArticles::execute(Database &db, MessageHandler &messageHandler)
{
    auto&& groups = db.getNewsGroups();

    auto&& articles = db.getArticles(group_id);
    messageHandler.sendCode(Protocol::ANS_LIST_ART);

    for(auto it = groups.cbegin(); it != groups.cend(); ++it)
    {
        const Newsgroup &ng = *it;
        if(ng.getId() == group_id)
        {
            messageHandler.sendCode(Protocol::ANS_ACK);
            messageHandler.sendIntParameter(articles.size());
            for(auto& article : articles)
            {
                messageHandler.sendIntParameter(std::stoi(article->getId()));
                messageHandler.sendStringParameter(article->getTitle());
                std::cout << "article->getId()()" << article->getId() << std::endl;
                std::cout << "article->getTitle()" << article->getTitle() << std::endl;
            }

            messageHandler.sendCode(Protocol::ANS_END);
            return;
        }
    }

    messageHandler.sendCode(Protocol::ANS_NAK);
    messageHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
    messageHandler.sendCode(Protocol::ANS_END);


}

std::string CreateArticle::extractString(const std::vector<Protocol>& tokens, size_t index, int length) {
    std::string result;
    for (int i = 0; i < length; ++i) {
        result += static_cast<char>(static_cast<int>(tokens[index + i]));
    }
    return result;
}

CreateArticle::CreateArticle(const std::vector<Protocol> &tokenized_string)
{
    if (tokenized_string.size() < 13 ||
        tokenized_string[0] != Protocol::COM_CREATE_ART ||
        tokenized_string[1] != Protocol::PAR_NUM ||
        tokenized_string.back() != Protocol::COM_END)
    {
        throw std::invalid_argument("Invalid command format");
    }

    group_id = std::to_string(readNumber(tokenized_string, 2));

    size_t index = 6;

    auto parseStringParam = [&](std::string& outStr) {
        if (index >= tokenized_string.size() || tokenized_string[index] != Protocol::PAR_STRING) {
            throw std::invalid_argument("Expected PAR_STRING");
        }
        ++index;

        if (index >= tokenized_string.size()) {
            throw std::invalid_argument("Expected string length after PAR_STRING");
        }

        //int len = static_cast<int>(tokenized_string[index]);
        int len = readNumber(tokenized_string, index);
        index += 4;

        outStr = extractString(tokenized_string, index, len);
        index += len;
    };

    parseStringParam(title);
    parseStringParam(author);
    parseStringParam(text);

}

void CreateArticle::execute(Database &db, MessageHandler &messageHandler)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 10000);
    int random_number = distr(gen);
    messageHandler.sendCode(Protocol::ANS_CREATE_ART);
    auto&& groups = db.getNewsGroups();
    for(auto it = groups.cbegin(); it != groups.cend(); ++it)
    {

        const Newsgroup &ng = *it;
        if(ng.getId() == group_id)
        {
            messageHandler.sendCode(Protocol::ANS_ACK);
            auto article = std::make_shared<Article>(title, author, text, std::time(nullptr), std::to_string(random_number));
            db.addArticle(article, ng);
            messageHandler.sendCode(Protocol::ANS_END);
            return;
        }
    }

    messageHandler.sendCode(Protocol::ANS_NAK);
    messageHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
    messageHandler.sendCode(Protocol::ANS_END);
}

GetArticle::GetArticle(const std::vector<Protocol> &tokenized_string)
{
    group_id = std::to_string(readNumber(tokenized_string, 2));
    article_id = std::to_string(readNumber(tokenized_string, 7));
}


void GetArticle::execute(Database &db, MessageHandler &messageHandler)
{
    messageHandler.sendCode(Protocol::ANS_GET_ART);
    auto&& groups = db.getNewsGroups();
    for(auto it = groups.cbegin(); it != groups.cend(); ++it)
    {
        const Newsgroup &ng = *it;
        if(ng.getId() == group_id)
        {
            auto article = db.getArticle(group_id, article_id);
            if(article != nullptr)
            {
                messageHandler.sendCode(Protocol::ANS_ACK);
                messageHandler.sendStringParameter(article->getTitle());
                messageHandler.sendStringParameter(article->getAuthor());
                messageHandler.sendStringParameter(article->getText());
                messageHandler.sendCode(Protocol::ANS_END);
                return;
            }
        }
    }

    messageHandler.sendCode(Protocol::ANS_NAK);
    auto&& articles = db.getArticles(group_id);
    if(articles.size() == 0)
    {
        messageHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    else
    {
        messageHandler.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
    }

    messageHandler.sendCode(Protocol::ANS_END);
}

DeleteArticle::DeleteArticle(const std::vector<Protocol> &tokenized_string)
{
    group_id = std::to_string(readNumber(tokenized_string, 2));
    article_id = std::to_string(readNumber(tokenized_string, 7));
}


void DeleteArticle::execute(Database &db, MessageHandler &messageHandler)
{
    messageHandler.sendCode(Protocol::ANS_DELETE_ART);
    auto&& groups = db.getNewsGroups();
    for(auto it = groups.cbegin(); it != groups.cend(); ++it)
    {
        const Newsgroup &ng = *it;
        if(ng.getId() == group_id)
        {

            auto&& articles = db.getArticles(group_id);
            for(auto it = articles.cbegin(); it != articles.cend(); ++it)
            {
                std::cout << "(*it)->getId()" << (*it)->getId() << std::endl;

                if(stoi((*it)->getId()) == stoi(article_id))
                {

                    db.deleteArticle(group_id, article_id);
                    messageHandler.sendCode(Protocol::ANS_ACK);
                    messageHandler.sendCode(Protocol::ANS_END);
                    return;
                }
            }
        }
    }

    messageHandler.sendCode(Protocol::ANS_NAK);
    auto&& articles = db.getArticles(group_id);
    if(articles.size() == 0)
    {
        messageHandler.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    else
    {
        messageHandler.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
    }

    messageHandler.sendCode(Protocol::ANS_END);
}
