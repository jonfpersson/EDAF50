#include "server_handler.h"

serverHandler::serverHandler(){

}

serverHandler::~serverHandler(){

}
/*
 * Read an integer from a client.
 */
int serverHandler::readNumber(const std::shared_ptr<Connection>& conn)
{
        unsigned char byte1 = conn->read();
        unsigned char byte2 = conn->read();
        unsigned char byte3 = conn->read();
        unsigned char byte4 = conn->read();
        return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

/*
 * Send a string to a client.
 */
void serverHandler::writeString(const std::shared_ptr<Connection>& conn, const string& s)
{
        for (char c : s) {
                conn->write(c);
        }
        conn->write('$');
}

Server serverHandler::init(int argc, char* argv[])
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

void serverHandler::process_request(std::shared_ptr<Connection>& conn)
{

        // read command byte(s)
        unsigned char byte = conn->read();

        /* logic here */

        //write back to server
        //writeString(conn, result);
}

void serverHandler::start(Server& server)
{
        auto conn = server.waitForActivity();
        if (conn != nullptr) {
                try {
                    process_request(conn);
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

int serverHandler::setup(int argc, char* argv[])
{
        auto server = init(argc, argv);

        while (true) {
                start(server);
        }
        return 0;
}
