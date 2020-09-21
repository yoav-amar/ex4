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

#define BACKLOG 20

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

uint16_t serverSide::AbstractServer::getSockfd(){
    return sockfd;
}

void serverSide::AbstractServer::init(uint16_t port){
    struct sockaddr_in address; 

    
    const auto sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        THROW_SYSTEM_ERROR();
    }
    
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sockfd, reinterpret_cast<const sockaddr*>(&address),
                    sizeof(address)) < 0) {
        close(sockfd);
        THROW_SYSTEM_ERROR();
    }

    if(listen(sockfd, BACKLOG) < 0){
        close(sockfd);
        THROW_SYSTEM_ERROR();
    }
    
}

void serverSide::SerialServer::open(uint16_t port,const client::ClientHandle& handeler){
    init(port);


}