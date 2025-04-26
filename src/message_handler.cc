#include "message_handler.hh"
#include "protocol.hh"
#include <ios>

MessageHandler::MessageHandler(std::shared_ptr<Connection> conn)
    : conn(conn) {}

void MessageHandler::sendByte(int code) {
     try {
         conn->write(static_cast<char>(code));
     } catch (const std::ios_base::failure&) {
         throw ConnectionClosedException();
     }
}

void MessageHandler::sendCode(Protocol code) {
    sendByte(static_cast<int>(code));
}

void MessageHandler::sendInt(int value) {
    sendByte((value >> 24) & 0xFF);
    sendByte((value >> 16) & 0xFF);
    sendByte((value >> 8) & 0xFF);
    sendByte(value & 0xFF);
}

void MessageHandler::sendIntParameter(int param) {
    sendCode(Protocol::PAR_NUM);
    sendInt(param);
}

void MessageHandler::sendStringParameter(const std::string& param) {
    sendCode(Protocol::PAR_STRING);
    sendInt(static_cast<int>(param.length()));
    for (char ch : param) {
        sendByte(static_cast<unsigned char>(ch));
    }
}

int MessageHandler::recvByte() {
    // int code = conn->read();
    // if (code == Connection::CONNECTION_CLOSED) {
    //     throw ConnectionClosedException();
    // }
    // return code;
    return 1;
}


int MessageHandler::recvCode() {
    // int code = recvByte();
    // return code;

    return 1;
}

int MessageHandler::recvInt() {
    // int b1 = recvByte();
    // int b2 = recvByte();
    // int b3 = recvByte();
    // int b4 = recvByte();

    // return b1 << 24 | b2 << 16 | b3 << 8 | b4;

    return 1;
}

int MessageHandler::recvIntParameter() {
    // int code = recvCode();
    // if (code != Protocol::PAR_NUM) {
    //     //error
    // }
    // return recvInt();
    return 1;
}

std::string MessageHandler::recvStringParameter() {
    // int code = recvCode();
    // if (code != Protocol::PAR_STRING) {
    //     //error
    // }
    // int n = recvInt();
    // if (n < 0) {
    //     //error
    // }

    // std::string result;
    // result.reserve(n);
    // for (int i = 0; i < n; ++i) {
    //     char ch = static_cast<char>(conn->read());
    //     result.push_back(ch);
    // }
    // return result;

    return "1";
}
