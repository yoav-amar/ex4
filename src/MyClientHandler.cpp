#include <iostream>
#include <string>
#include <errno.h>
#include <unistd.h>
#include <atomic>
#include <mutex>
#include "MyClientHandler.hpp"
#include "Problem.hpp"

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
  /**
   * @brief parse the rest of the problem to get the 
   * type of problem.
   * return true if it is a valid algorithem, false otherwise.
   *
   * @param msg the rest of the message.
   * @return bool
   */
bool parseTypeOfProblem(std::string& msg){
    while (msg[0] == ' ' || msg[0] == '\t')
    {
        //advance the space
        msg = msg.substr(1);
    }
    if(msg.compare("A*") != 0 && msg.compare("BFS") != 0
                     && msg.compare("DFS") != 0 && msg.compare("BestFS") != 0){
                         return false;
                     }
    return true;
}
bool parseFirstMsg(uint16_t out, std::string& msg, std::string & typeOfAlgorithem){
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
        typeOfAlgorithem = "BFS";
        printMsg(out, 0, "");
        return true;
    }
    else{
        if(parseTypeOfProblem(msg)){
            typeOfAlgorithem = msg;
            printMsg(out, 0, "");
            return true;
        }
        printMsg(out, 3, "");
        return false;
    }
}

void parseSecondMsg(uint16_t out, std::string& msg, std::string& typeOfAlgorithem){
    uint16_t numOfLinesLeft = 0;
    for(uint32_t j  = 0; j < msg.size(); ++j){
        if(msg[j] == '\n'){
            ++numOfLinesLeft;
        }
    }
    //go through all the message.
    int32_t i=0;
    std::string matrixString;
    std::string entryPoint;
    std::string endPoint;

    //two lines for break, one line to entry point and one line to end point.
    while (numOfLinesLeft > 4)
    {
        matrixString +=msg[i];
        //end of line.
        if(msg[i+1] == '\r' && msg[i+2] == '\n'){
            --numOfLinesLeft;
        }
        ++i;
    }
    //advance the counter to the next line.
    i +=2;
    while (msg[i] != '\r' && msg[i + 1] != '\n')
    {
        entryPoint += msg[i];
        ++i;
    }
    //advance the counter to the next line.
    i +=2;
    while (msg[i] != '\r' && msg[i + 1] != '\n')
    {
        endPoint += msg[i];
        ++i;
    }

    try{
        problem::Search searcher(matrixString, typeOfAlgorithem, entryPoint, endPoint, 3, 3);
        std::string result; 
        result = searcher.solveProblem();
        printMsg(out, 0, result);
    }catch(...){
        printMsg(out, 4, "");
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
    std::string message, typeOfAlgorithem;
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
                        if(!parseFirstMsg(out, tmp, typeOfAlgorithem)){
                            stop = true;
                        }
                        firstMsg = false;
                    }else{
                        std::cout << "parse second msg" << std::endl;
                        parseSecondMsg(out, message, typeOfAlgorithem);
                        stop = true;
                    }
                    message = message.substr(message.find("\r\n\r\n") + sizeof("\r\n\r\n") -1);
                }
            }
         }
    }
    std::cout << "bey" << std::endl;
    close(in);
}