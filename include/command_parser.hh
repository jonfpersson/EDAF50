
#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include "command.hh"

class CommandParser
{
public:
    std::unique_ptr<Command> parse(const std::vector<Protocol>& );
};

#endif 