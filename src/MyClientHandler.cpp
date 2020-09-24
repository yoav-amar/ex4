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
#include <mutex>
#include "MyClientHandler.hpp"

void printMsg(uint16_t out, int status, const std::string& msg){
    std::string fullMsg = "Version: 1.0\r\nstatus: ";
    fullMsg += std::to_string(status);
    fullMsg += "\r\nresponse-length: ";
    fullMsg += std::to_string(msg.length());
    if(msg.length() != 0){
        fullMsg += "\r\n\r\n" + msg;
    }
    fullMsg += "\r\n\r\n";
    if(write(out, fullMsg.data(), fullMsg.length()) < 0){
        //throw exception
    }
}

void parseFirstMsg(uint16_t out, std::string& msg){
    if(msg.find("solve") != 0){
        printMsg(out, 1, "");
    }
    //advance the string after the sub string 'solve'
    msg = msg.substr(sizeof("solve") -1);
    while (msg[0] == ' ' || msg[0] == '\t')
    {
        //advance the space
        msg = msg.substr(1);
    }
    if(msg.find("find-graph-path") != 0){
        printMsg(out, 1, "");
    }
    //advance the string after the sub string 'find-graph-path'
    msg = msg.substr(sizeof("find-graph-path") -1);
    while (msg[0] == ' ' || msg[0] == '\t')
    {
        //advance the space
        msg = msg.substr(1);
    }
    //the defualt algorithem.
    if(!msg.compare("")){
        printMsg(out, 0, "");
    }else{
        try{
            //
            printMsg(out, 0, "");
        }
         catch(const std::exception& e)
        {
            printMsg(out, 2, "");
        }
    }
    
}

void parseSecondMsg(uint16_t out, std::string& msg){

}

void handle::ClientHandle::handleClient(std::uint16_t out,std::uint16_t in) const{
    bool firstMsg=true;
    std::mutex mut;
    std::unique_lock<std::mutex> lck (mut, std::defer_lock);
    std::atomic_bool stop;
    stop = false;
    std::string buffer(1024, '\0');
    std::string message;
    const std::string emptyString(1024, '\0');
    const std::chrono::seconds watingTime (5);
    lck.lock();
    auto start = std::chrono::steady_clock::now();
    auto end = start;
    lck.unlock();
    while(!stop){
        const auto numBytesRead = read(in, (void*)(buffer.data()), buffer.size() - 1);
        if (numBytesRead < 0) {
            //std::cout << "bey" << std::endl;
            close(in);
        }
        buffer[numBytesRead] = '\0';
        if(buffer.compare(0, numBytesRead, "\0") != 0){
            //std::cout << "got" << std::endl;
            message += buffer.substr(0, numBytesRead);
            if(message.find("\r\n\r\n") != -1){
                if(firstMsg){
                    std::string tmp =  message.substr(0, message.find("\r\n\r\n"));
                    parseFirstMsg(out, tmp);
                    firstMsg = false;
                }
                else
                {
                    parseSecondMsg(out, message);
                    stop = true;
                }
                
                message = message.substr(message.find("\r\n\r\n") + sizeof("\r\n\r\n") -1);
            }
        }
        end = std::chrono::steady_clock::now();
        if(end - start > watingTime){
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
            stop = true;
        }

    }
    close(in);
}