#include "Server.hpp"

void initThreeArgs(serverSide::Server*& server, const std::string& kindOfServer){
    if(kindOfServer.compare("parallel") == 0){
        server = new serverSide::ParallelServer();
    }
    else if(kindOfServer.compare("serial") == 0){
        server = new serverSide::SerialServer();
    }
    else
    {
        //error
    }
}

int main(int argc, char** argv) {
    serverSide::Server* server;
    if(argc == 3){
        std::string kindOfServer = argv[2];
        initThreeArgs(server, kindOfServer);
    }
    else if(argc == 2){
        server = new serverSide::ParallelServer();
    }
    else
    {
        //error
    }
}