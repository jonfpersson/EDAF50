#include "connection.h"
#include "connectionclosedexception.h"
#include "server.h"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

class serverHandler {

    public:
    serverHandler();
    ~serverHandler();

    int readNumber(const std::shared_ptr<Connection>& conn);
    void writeString(const std::shared_ptr<Connection>& conn, const string& s);
    Server init(int argc, char* argv[]);
    void process_request(std::shared_ptr<Connection>& conn);
    void start(Server& server);
    int setup(int argc, char* argv[]);
    
    
    private:

};