#include "command_parser.hh"
#include "commands.hh"
#include "command.hh"
#include <regex>
#include <vector>
#include <cstring>
#include "utils.hh"

std::unique_ptr<Command> CommandParser::parse(const std::vector<Protocol> &commandStr)
{
    Protocol command_type = commandStr[0];

    if (command_type == Protocol::COM_LIST_NG)
    {
        return std::unique_ptr<Command>(new ListNG(commandStr));
    }
    else if (command_type == Protocol::COM_CREATE_NG)
    {
        return std::unique_ptr<Command>(new CreateNG(commandStr));
    }
    else if (command_type == Protocol::COM_DELETE_NG)
    {
        return std::unique_ptr<Command>(new DeleteNG(commandStr));
    }
    else if (command_type == Protocol::COM_LIST_ART)
    {
        return std::unique_ptr<Command>(new ListArticles(commandStr));
    }
    else if (command_type == Protocol::COM_CREATE_ART)
    {
        return std::unique_ptr<Command>(new CreateArticle(commandStr));
    }
    else if (command_type == Protocol::COM_GET_ART)
    {
        return std::unique_ptr<Command>(new GetArticle(commandStr));
    }
    else if (command_type == Protocol::COM_DELETE_ART)
    {
        return std::unique_ptr<Command>(new DeleteArticle(commandStr));
    }
    else
    {
        throw std::invalid_argument("Invalid command type");
    }
}