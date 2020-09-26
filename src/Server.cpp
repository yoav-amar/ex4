#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <mutex>
#include <queue>
#include <thread>
#include <iostream>
#include <string_view>
#include <system_error>

#include "MyClientHandler.hpp"
#include "Server.hpp"

#define LISTEN_SIZE 20

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

std::mutex g_mut;

std::uint16_t serverSide::AbstractServer::getSockfd(){
    return m_sockfd;
}

std::uint16_t serverSide::AbstractServer::getSockfd(){
    return m_sockfd;
}


void serverSide::AbstractServer::init(std::uint16_t port){
    sockaddr_in address{};
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sockfd < 0) {
        THROW_SYSTEM_ERROR();
    }
    
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(m_sockfd, reinterpret_cast<const sockaddr*>(&address),
                    sizeof(address)) < 0) {
        close(m_sockfd);
        THROW_SYSTEM_ERROR();
    }

    if(listen(m_sockfd, LISTEN_SIZE) < 0){
        close(m_sockfd);
        THROW_SYSTEM_ERROR();
    }
    
}

bool serverSide::AbstractServer::isRunning(){
    return !m_isStop;
}

void serverSide::AbstractServer::stop(){
    m_isStop = true;
}

void serverSide::SerialServer::open(std::uint16_t port, const handle::ClientHandle& handeler){
    init(port);
    int16_t clientSocket, addlen;
    while (isRunning())
    {
        sockaddr_in recive{};
        addlen = sizeof(recive);
        clientSocket = accept(getSockfd(), reinterpret_cast<sockaddr*>(&recive),
                    reinterpret_cast<socklen_t*>(&addlen));
        if(clientSocket < 0){
            close(getSockfd());
            THROW_SYSTEM_ERROR(); 
        }
        std::cout << "accepting new client" << std::endl;
        handeler.handleClient(clientSocket, clientSocket);
        
    }
}

void serverSide::ParallelServer::open(std::uint16_t port, const handle::ClientHandle& handeler){
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
    close(getSockfd());
}