#include "message_handler.hh"
#include "protocol.hh"
#include "connectionclosedexception.hh"
#include <ios>
#include <ostream>
#include <iostream>
inline bool operator==(int value, Protocol protocol)
{
    return static_cast<int>(protocol) == value;
}

inline bool operator!=(int value, Protocol protocol)
{
    return static_cast<int>(protocol) != value;
}

MessageHandler::MessageHandler(std::shared_ptr<Connection> conn)
    : conn(conn) {}

void MessageHandler::sendByte(int code)
{
    try
    {
        conn->write(static_cast<char>(code));
        // std::cout << "wrote to client: " << (int) code << std::endl;
    }
    catch (const std::ios_base::failure &)
    {
        throw ConnectionClosedException();
    }
}

void MessageHandler::sendCode(Protocol code)
{
    sendByte(static_cast<int>(code));
}

void MessageHandler::sendInt(int value)
{
    sendByte((value >> 24) & 0xFF);
    sendByte((value >> 16) & 0xFF);
    sendByte((value >> 8) & 0xFF);
    sendByte(value & 0xFF);
}

void MessageHandler::sendIntParameter(int param)
{
    sendCode(Protocol::PAR_NUM);
    sendInt(param);
}

void MessageHandler::sendStringParameter(const std::string &param)
{
    sendCode(Protocol::PAR_STRING);
    sendInt(static_cast<int>(param.length()));
    for (char ch : param)
    {
        sendByte(static_cast<unsigned char>(ch));
    }
}

int MessageHandler::recvByte()
{
    return conn->read();
}

int MessageHandler::recvCode()
{
    return recvByte();
}

int MessageHandler::recvInt()
{
    int b1 = recvByte();
    int b2 = recvByte();
    int b3 = recvByte();
    int b4 = recvByte();

    return (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
}

int MessageHandler::recvIntParameter()
{
    int code = recvCode();
    if (code != Protocol::PAR_NUM)
    {
        throw ConnectionClosedException();
    }
    return recvInt();
}

std::string MessageHandler::recvStringParameter()
{
    int code = recvCode();
    if (code != Protocol::PAR_STRING)
    {
        throw ConnectionClosedException();
    }

    int n = recvInt();
    if (n < 0)
    {
        throw "Invalid paramter";
    }

    std::string result;
    result.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        char ch = static_cast<char>(recvByte());
        result.push_back(ch);
    }

    return result;
}
