#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string_view>
#include <system_error>

#include "ClientHandle.hpp"
#include "Server.hpp"

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }



void serverSide::AbstractServer::init(uint16_t port){
        struct sockaddr_in address; 

    
    const auto sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        THROW_SYSTEM_ERROR();
    }

    //should add

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
}

void serverSide::SerialServer::open(uint16_t port,const client::ClientHandle& handeler){
    init(port);


}