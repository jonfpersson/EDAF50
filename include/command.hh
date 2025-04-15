#ifndef COMMAND_H
#define COMMAND_H

#include "database.hh"
#include "connection.hh"
#include "message_handler.hh"

class Command
{
public:
    virtual ~Command() = default; 
    Command() = default;

    virtual void execute(Database& db, MessageHandler& messageHandler) = 0;
};

#endif