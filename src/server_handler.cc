#include "connection.hh"
#include "connectionclosedexception.hh"
#include "server.hh"
#include "protocol.hh"
#include "command_parser.hh"
#include "database_disk.hh"
#include "database_ram.hh"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using std::cerr;
using std::cout;
using std::endl;
using std::string;

Server init(int argc, char *argv[])
{
        if (argc != 2)
        {
                cerr << "Usage: myserver port-number" << endl;
                exit(1);
        }

        int port = -1;
        try
        {
                port = std::stoi(argv[1]);
        }
        catch (std::exception &e)
        {
                cerr << "Wrong format for port number. " << e.what() << endl;
                exit(2);
        }

        Server server(port);
        if (!server.isReady())
        {
                cerr << "Server initialization error." << endl;
                exit(3);
        }
        return server;
}

void process_request(std::shared_ptr<Connection> &conn, Database &db)
{
        static std::vector<Protocol> command_string;
        static int remaining = 0;
        MessageHandler messageHandler(conn);
        unsigned char byte = conn->read();
        command_string.push_back((Protocol)byte);
        std::cout << "Read byte: " << (int)byte << std::endl;

        if (remaining > 0)
        {
                remaining--;
                return;
        }

        // if this is a PAR_STRING, the next byte is the length
        if (byte == (int)Protocol::PAR_STRING)
        {
                remaining = -1; // next byte will tell us how many characters to read
        }
        else if (remaining == -1)
        {
                remaining = byte; // byte is the length of the string
        }
        else if (byte == (int)Protocol::PAR_NUM)
        {
                remaining = 4; // one byte of number data will follow
        }
        else if (byte == (int)Protocol::COM_END)
        {
                CommandParser parser;
                parser.parse(command_string)->execute(db, messageHandler);
                command_string.clear();
        }
}

void start(Server &server, Database &db)
{
        while (true)
        {
                auto conn = server.waitForActivity();
                if (conn != nullptr)
                {
                        try
                        {
                                process_request(conn, db);
                        }
                        catch (ConnectionClosedException &)
                        {
                                server.deregisterConnection(conn);
                                cout << "Client closed connection" << endl;
                        }
                        catch (std::invalid_argument &e)
                        {
                                cerr << "Error: Protocol violation detected." << endl;
                                cerr << "Disconnecting client..." << endl;
                                server.deregisterConnection(conn);
                        }
                        catch (...)
                        {
                                cerr << "Server error detected." << endl;
                                cerr << "Disconnecting client..." << endl;
                                server.deregisterConnection(conn);
                                return;
                        }
                }
                else
                {
                        conn = std::make_shared<Connection>();
                        server.registerConnection(conn);
                        cout << "New client connects" << endl;
                }
        }
}

int main(int argc, char *argv[])
{
        auto server = init(argc, argv);
        DatabaseRam db_ram;
        DatabaseDisk db_disk;

        start(server, db_disk);

        return 0;
}
