#include "command_parser.hh"
#include "commands.hh"
#include "command.hh"
#include <regex>
#include <vector>
#include <cstring>
#include "utils.hh"

std::unique_ptr<Command> CommandParser::parse(const std::string &commandStr)
{
    std::vector<std::string> command_string_tokenized = split(commandStr, " ");
    std::string command_type = command_string_tokenized[0];

    try
    {
        if (command_type == "COM_LIST_NG")
        {
            return std::unique_ptr<Command>(new ListNG(command_string_tokenized));
        }
        else if (command_type == "COM_CREATE_NG")
        {
            return std::unique_ptr<Command>(new CreateNG(command_string_tokenized));
        }
        else if (command_type == "COM_DELETE_NG")
        {
            return std::unique_ptr<Command>(new DeleteNG(command_string_tokenized));
        }
        else if (command_type == "COM_LIST_ART")
        {
            return std::unique_ptr<Command>(new ListArticles(command_string_tokenized));
        }
        else if (command_type == "COM_CREATE_ART")
        {
            return std::unique_ptr<Command>(new CreateArticle(command_string_tokenized));
        }
        else if (command_type == "COM_GET_ART")
        {
            return std::unique_ptr<Command>(new GetArticle(command_string_tokenized));
        }
        else if (command_type == "COM_DELETE_ART")
        {
            return std::unique_ptr<Command>(new DeleteArticle(command_string_tokenized));
        }
        else{
            return std::unique_ptr<Command>(new Invalid(std::vector<std::string>()));
        }
    }
    catch (...)
    {
        return std::unique_ptr<Command>(new Invalid(std::vector<std::string>()));
    }

}