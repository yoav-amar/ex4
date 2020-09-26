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
    class AbstractServer : public Server{
        private:
            std::int16_t m_sockfd;
            bool m_isStop;
        protected:
        /**
         * @brief return the socket file descriptor.
         * 
         * @return std::uint16_t
         */
            std::uint16_t getSockfd();
        /**
         * @brief initialize the server.
         * 
         * @param port the port the server listen to.
         */
            void init(std::uint16_t port);
        /**
         * @brief return true if the program should still running.
         * 
         * @return bool
         */
            bool isRunning();
        public:
        /**
         * @brief stop the server.
         */
            void stop();
        
    };

    /**
    * @brief a server that handle clients one after the other.          
    */
    class SerialServer : public AbstractServer{
        public:
        /**
         * @brief open a new server.
         * 
         * @param port the port the server listen to.
         * @param handeler handel the clients
         */
            void open(std::uint16_t port, const handle::ClientHandle& handeler);
    };
    
    /**
    * @brief a server that handle clients simultaneously. 
    * use threads.         
    */
    class ParallelServer : public AbstractServer{
        private:
        /**
         * @brief an infinate loop func that the threads call.
         * helps handle the clients
         * 
         * @param sockQueue the queue of clients that are wating to be handled.
         * @param handeler handele the clients.
         */
            void threadFunc(std::queue<std::uint16_t>& sockQueue, const handle::ClientHandle& handeler);
        public:
        /**
         * @brief open a new server.
         * 
         * @param port the port the server listen to.
         * @param handeler handel the clients
         */
            void open (std::uint16_t port, const handle::ClientHandle& handeler);
    };
    
}