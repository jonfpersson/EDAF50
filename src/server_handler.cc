#include "connection.hh"
#include "connectionclosedexception.hh"
#include "server.hh"
#include "protocol.hh"
#include "command_parser.hh"
#include "database_disk.hh"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using std::string;
using std::cout;
using std::cerr;
using std::endl;


Server init(int argc, char* argv[])
{
        if (argc != 2) {
                cerr << "Usage: myserver port-number" << endl;
                exit(1);
        }

        int port = -1;
        try {
                port = std::stoi(argv[1]);
        } catch (std::exception& e) {
                cerr << "Wrong format for port number. " << e.what() << endl;
                exit(2);
        }

        Server server(port);
        if (!server.isReady()) {
                cerr << "Server initialization error." << endl;
                exit(3);
        }
        return server;
}

void process_request(std::shared_ptr<Connection>& conn, Database& db)
{
        MessageHandler messageHandler(conn);

        static std::vector<Protocol> command_string;

        unsigned char byte = conn->read();
        command_string.push_back((Protocol)byte);
    //for(Protocol p : tokenized_string){
    std::cout << (int)byte << std::endl;

    //}

        if(byte == (char) Protocol::COM_END){
                CommandParser parser;

                parser.parse(command_string)->execute(db, messageHandler);
                command_string.clear();

        }

}

void start(Server& server)
{
        DatabaseDisk db;
        auto conn = server.waitForActivity();
        if (conn != nullptr) {
                try {
                    process_request(conn, db);
                } catch (ConnectionClosedException&) {
                        server.deregisterConnection(conn);
                        cout << "Client closed connection" << endl;
                }
        } else {
                conn = std::make_shared<Connection>();
                server.registerConnection(conn);
                cout << "New client connects" << endl;
        }
}

int main(int argc, char* argv[])
{
        auto server = init(argc, argv);
        while (true) {
                start(server);
        }
        return 0;
}
