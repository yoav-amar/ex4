#pragma once
#include <iostream>
#include "MyClientHandler.hpp"
namespace serverSide{
    class Server
    {
    private:
        
    public:
        virtual void open(std::uint16_t port,const const handle::ClientHandle& handeler) = 0;
        virtual void stop() = 0;
    };
    class AbstractServer : Server{
        private:
            std::uint16_t m_sockfd;
            bool m_isStop;
        protected:
            struct sockaddr_in address;
            std::uint16_t getSockfd();
            void init(std::uint16_t port);
            bool isRunning();
        public:
            void stop();
        
    };
    class SerialServer : AbstractServer{
        void open(std::uint16_t port, const handle::ClientHandle& handeler);
    };

    class ParallelServer : AbstractServer{
        void open (std::uint16_t port, const handle::ClientHandle& handeler);
    };
    
}