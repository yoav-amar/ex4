#include <iostream>
#include <string>
#include <errno.h>
#include <unistd.h>
#include <atomic>
#include <mutex>
#include "MyClientHandler.hpp"

#define WAIT_FOR_OUT 5

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
        close(out);
        throw std::system_error { errno, std::system_category() };
    }
}
bool parseFirstMsg(uint16_t out, std::string& msg){
    if(msg.find("solve ") != 0 && msg.find("solve\t") != 0){
        printMsg(out, 1, "");
        return false;
    }
    //advance the string after the sub string 'solve'
    msg = msg.substr(sizeof("solve") -1);
    while (msg[0] == ' ' || msg[0] == '\t')
    {
        //advance the space
        msg = msg.substr(1);
    }
    if(msg.find("find-graph-path") != 0){
        printMsg(out, 2, "");
        return false;
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
        return true;
    }
    else{
        try{
            //
            printMsg(out, 0, "");
        }
         catch(const std::exception& e)
        {
            printMsg(out, 3, "");
        }
    }
    return true;
}

void parseSecondMsg(uint16_t out, std::string& msg){
    if(out){

    }
    if(!msg.compare("hey")){

    }

}

void handle::ClientHandle::handleClient(std::uint16_t out,std::uint16_t in) const{
    //set timing, the tmp because select is destructive.
    fd_set set, tmpSet;
    FD_ZERO(&set);
    FD_SET(out, &set);
    bool firstMsg=true;
    std::mutex mut;
    std::unique_lock<std::mutex> lck (mut, std::defer_lock);
    std::atomic_bool stop;
    stop = false;
    std::string buffer(1024, '\0');
    std::string message;
    while(!stop){
        //set timout here because select is destructive.
        tmpSet = set;
        struct timeval timeout;
        timeout.tv_sec = WAIT_FOR_OUT;
        timeout.tv_usec = 0;
        int waitToRead = select(in + 1, &tmpSet, nullptr, nullptr, &timeout);
        if(waitToRead <= 0){
            std::cout << "waiting time is over, client is too slow" << std::endl;
            close(in);
            return;
        }
        if(FD_ISSET(in, &tmpSet)){
            const auto numBytesRead = read(in, (void*)(buffer.data()), buffer.size() - 1);
            if (numBytesRead < 0) {
                close(in);
                throw std::system_error { errno, std::system_category() };
            }
            buffer[numBytesRead] = '\0';
            if(buffer.compare(0, numBytesRead, "\0") != 0){
                message += buffer.substr(0, numBytesRead);
                std::size_t t = -1;
                if(message.find("\r\n\r\n") != t){
                    if(firstMsg){
                        std::string tmp =  message.substr(0, message.find("\r\n\r\n"));
                        if(!parseFirstMsg(out, tmp)){
                            stop = true;
                        }
                        std::cout << "wait for second message" << std::endl;
                        firstMsg = false;
                    }else{
                        parseSecondMsg(out, message);
                        stop = true;
                    }
                    message = message.substr(message.find("\r\n\r\n") + sizeof("\r\n\r\n") -1);
                }
            }
         }
    }
    close(in);
}