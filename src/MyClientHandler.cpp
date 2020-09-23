#include <iostream>
#include <string>
#include <fstream>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "ClientHandle.hpp"
void handle::ClientHandle::handleClient(std::uint16_t out,std::uint16_t in) const{
    std::int16_t x = write(in, "7897", 4);
    std::cout << x << std::endl;
    std::cout <<"opp" << std::endl;
    std::string buffer(1024, '\0');
    const std::string emptyString(1024, '\0');
    std::cout <<"ouo" << std::endl;
    while(true){
        const auto numBytesRead = read(in, (void*)(buffer.data()), buffer.size() - 1);
        if (numBytesRead < 0) {
            close(in);
        }
        buffer[numBytesRead] = '\0';
        if(buffer.compare(0, numBytesRead, "\0") != 0){
            write(out, buffer.data(), numBytesRead);
            buffer = emptyString;
        }
    }
    close(in);
}