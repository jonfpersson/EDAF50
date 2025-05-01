#ifndef COMMANDS_H
#define COMMANDS_H

#include "database.hh"
#include "message_handler.hh"
#include "command.hh"

class ListNG : public Command
{
    public:
    ListNG(const std::vector<Protocol>&  command_string_tokenized);
    void execute(Database&, MessageHandler&) override;
};

class CreateNG : public Command
{
    private:
    std::string name;
    std::string id;

    public:
    CreateNG(const std::vector<Protocol>&  command_string_tokenized);
    void execute(Database&, MessageHandler&) override;
};

class DeleteNG : public Command
{
    private:
    std::string id;
    public:
    DeleteNG(const std::vector<Protocol>&  command_string_tokenized);
    void execute(Database&, MessageHandler&) override;
};

class ListArticles : public Command
{
    private:
    std::string group_id;
    public:
    ListArticles(const std::vector<Protocol>&  command_string_tokenized);
    void execute(Database&, MessageHandler&) override;
};

class CreateArticle : public Command
{
    private:
    std::string group_id;
    std::string title;
    std::string text;
    std::string author;
    public:
    CreateArticle(const std::vector<Protocol>&  command_string_tokenized);
    void execute(Database&, MessageHandler&) override;
    std::string extractString(const std::vector<Protocol>& tokens, size_t index, int length);

};

class GetArticle : public Command
{
    private:
    std::string group_id;
    std::string article_id;
    public:
    GetArticle(const std::vector<Protocol>&  command_string_tokenized);
    void execute(Database&, MessageHandler&) override;
};

class Invalid : public Command
{
    public:
    Invalid(const std::vector<Protocol>&  command_string_tokenized);
    void execute(Database&, MessageHandler&) override;
};

class DeleteArticle : public Command
{
    private:
    std::string group_id;
    std::string article_id;
    public:
    DeleteArticle(const std::vector<Protocol>&  command_string_tokenized);
    void execute(Database&, MessageHandler&) override;
};

#endif
