#include <iostream>
#include <string>
#include <fstream>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <atomic>
#include <unistd.h>
#include <chrono>
#include "MyClientHandler.hpp"

void printMsg(uint16_t out, uint16_t status, std::string& msg){
    std::string fullMsg = "Version: 1.0\r\n status: ";
    fullMsg += status;
    fullMsg += "\r\n response-length: ";
    fullMsg += msg.length();
    if(msg.length() != 0){
        fullMsg += "\r\n\r\n" + msg;
    }
    fullMsg += "\r\n\r\n";
    if(write(out, fullMsg.data(), fullMsg.length()));
}
void handle::ClientHandle::handleClient(std::uint16_t out,std::uint16_t in) const{
    
    std::atomic_bool stop(false);
    std::string buffer(1024, '\0');
    const std::string emptyString(1024, '\0');
    const std::chrono::seconds watingTime (5);
    auto start = std::chrono::steady_clock::now();
    auto end = start;
    while(!stop){
        const auto numBytesRead = read(in, (void*)(buffer.data()), buffer.size() - 1);
        if (numBytesRead < 0) {
            std::string tmp = "";
            printMsg(in, 1, tmp);
            close(in);
        }
    }
}