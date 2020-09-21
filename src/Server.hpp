#pragma once
#include <iostream>
#include "ClientHandle.hpp"
namespace serverSide{
    class Server
    {
    private:
        
    public:
        virtual void open(int16_t port,const client::ClientHandle& handeler) = 0;
        virtual void stop() = 0;
    };

    class SerialServer : Server{
    };
    
}