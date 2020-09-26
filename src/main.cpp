#include "Server.hpp"
#include "CacheException.hpp"

void initThreeArgs(serverSide::Server*& server, const std::string& kindOfServer){
    if(kindOfServer.compare("parallel") == 0){
        server = new serverSide::ParallelServer();
    }
    else if(kindOfServer.compare("serial") == 0){
        server = new serverSide::SerialServer();
    }
    else
    {
        throw cacheExcption::CacheExcpetion(error::error_not_supported_this_kind_of_problem);
    }
}

int main(int argc, char** argv) {
    try
    {
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
        throw cacheExcption::CacheExcpetion(error::error_wrong_number_of_arguments);  
    }
    int port = std::stoi(argv[1]);
    server->open(port,handle::ClientHandle());
    }
    catch(const cacheExcption::CacheExcpetion& e){
        e.printErrorMessage();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}