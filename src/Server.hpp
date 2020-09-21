#pragma once
#include <iostream>
#include "ClientHandle.hpp"
namespace serverSide{
    class Server
    {
    private:
        
    public:
        virtual void open(uint16_t port,const client::ClientHandle& handeler) = 0;
        virtual void stop() = 0;
    };
    class AbstractServer : Server{
        private:
            uint16_t sockfd;
        protected:
            uint16_t getSockfd();
            void init(uint16_t port);
    };
    class SerialServer : AbstractServer{
        void open(uint16_t port,const client::ClientHandle& handeler);
        void stop();
    };
    
}