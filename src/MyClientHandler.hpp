#pragma once

#include <iostream>

#include "CacheManager.hpp"
#include "Problem.hpp"

namespace Handle{
    class ClientHandle{
        private:

        public:
        void handleClient(std::uint16_t out,std::uint16_t in) const;
    };

}