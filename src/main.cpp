#include "Server.hpp"

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