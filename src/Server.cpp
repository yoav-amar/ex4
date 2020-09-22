#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <thread>
#include <iostream>
#include <string_view>
#include <system_error>

#include "ClientHandle.hpp"
#include "Server.hpp"

#define BACKLOG 20

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

std::uint16_t serverSide::AbstractServer::getSockfd(){
    return sockfd;
}

void serverSide::AbstractServer::init(std::uint16_t port){
     
 
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

bool serverSide::AbstractServer::isRunning(){
    return !isStop;
}

void serverSide::AbstractServer::stop(){
    isStop = true;
}

void serverSide::SerialServer::open(std::uint16_t port, const client::ClientHandle& handeler){
    init(port);
    sockaddr_in recive{};
    int clientSocket, len;
    while (isRunning())
    {
        len = sizeof(recive);
        clientSocket = accept(getSockfd(), reinterpret_cast<sockaddr*>(&recive),
                    reinterpret_cast<socklen_t*>(&len));
        if(clientSocket < 0){
            close(getSockfd());
            THROW_SYSTEM_ERROR(); 
        }
        //handle
    }


}

void serverSide::ParallelServer::open(std::uint16_t port, const client::ClientHandle& handeler){
    init(port);
    sockaddr_in recive{};
    int clientSocket, len;
    while (isRunning())
    {
        len = sizeof(recive);
        clientSocket = accept(getSockfd(), reinterpret_cast<sockaddr*>(&recive),
                    reinterpret_cast<socklen_t*>(&len));
        if(clientSocket < 0){
            close(getSockfd());
            THROW_SYSTEM_ERROR(); 
        }
        //handle
        
    }
}