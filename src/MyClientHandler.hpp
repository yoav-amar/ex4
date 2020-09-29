#pragma once

#include <iostream>

#include "Problem.hpp"

namespace handle{
    /**
     * @brief handle a client.
     * connect with the client with a socket.
     * 
     */
    class ClientHandle{
        public:
    /**
     * @brief handle the client.
     * 
     * @param out the socket for writing.
     * @param in the socket for reading.
     */
        void handleClient(std::uint16_t out,std::uint16_t in) const;
    };

}