#pragma once
#include <iostream>
#include <queue>
#include "MyClientHandler.hpp"
namespace serverSide{
    /**
     * @brief the interface of the server.
    */
    class Server
    {
    public:
        /**
         * @brief open a new server.
         * 
         * @param port the port the server listen to.
         * @param handeler handel the clients
         */
        virtual void open(std::uint16_t port,const handle::ClientHandle& handeler) = 0;
        /**
         * @brief stop the server.
         */
        virtual void stop() = 0;
        /**
         * @brief Destroy the server
         * 
         */
        virtual ~Server() = default;
    };
    /**
    * @brief an abstruct class to share code.          
    */
    class AbstractServer : Server{
        private:
            std::int16_t m_sockfd;
            bool m_isStop;
        protected:
            std::uint16_t getSockfd();
            void init(std::uint16_t port);
            bool isRunning();
        public:
            void stop();
        
    };
    class SerialServer : AbstractServer{
        public:
            void open(std::uint16_t port, const handle::ClientHandle& handeler);
    };

    class ParallelServer : AbstractServer{
        private:
            void threadFunc(std::queue<std::uint16_t>& sockQueue, const handle::ClientHandle& handeler);
        public:
            void open (std::uint16_t port, const handle::ClientHandle& handeler);
    };
    
}