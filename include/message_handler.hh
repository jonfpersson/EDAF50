#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "connection.hh"
#include "protocol.hh"
#include "connectionclosedexception.hh"
#include <string>
#include <memory>

class MessageHandler {
public:
    explicit MessageHandler(std::shared_ptr<Connection> conn);

    void sendCode(Protocol code);
    void sendInt(int value);
    void sendIntParameter(int param);
    void sendStringParameter(const std::string& param);

    int recvCode();
    int recvInt();
    int recvIntParameter();
    std::string recvStringParameter();

private:
    void sendByte(int code);
    int recvByte();

    std::shared_ptr<Connection> conn;
};

#endif
