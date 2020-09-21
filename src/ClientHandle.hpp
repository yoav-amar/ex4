#pragma once
#include <string>
#include "CacheManager.hpp"
namespace client{
    class ClientHandle
    {
    private:
        manager::CacheManager* m_cache;
        std::string m_nameOfProblem;
        std::string m_typeOfProblem;
        std::vector<std::string> m_inputFiles;
        std::string m_outpotFile;
        /**
         * @brief solve when the problem is cache.
         * 
         */
        void solveCache();
        /**
         * @brief build the client handle when the problem is cache.
         * 
         * @param argc the number of arguments from the main.
         * @param argv the arguments.
         */
        void buildCacheProblem(int argc, char** argv);
    public:
    /**
     * @brief Construct a new Client Handle object
     * 
         * @param argc the number of arguments from the main.
         * @param argv the arguments.
     */
        ClientHandle(int argc, char** argv);
        /**
         * @brief solve the problem.
         * 
         */
        void solve();
    };
    

    
}