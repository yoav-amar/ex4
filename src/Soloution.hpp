#pragma once

#include <string>
#include <cstdint>
#include "StatesPair.hpp"
#include <vector>
#include "Maze.hpp"
#include <queue>
namespace soloution {
    class Soloution {
        private:
        std::string m_pathToSoloution;
        uint32_t m_cost;
        uint32_t m_numberOfVertices;
        uint32_t m_numberOfDevelopedVetices;

        public:
        /**
         * @brief restore a solotion of the maze after receiving a vector of used pairs of the search.
         * 
         * @param pairs is a vector of pairs who have been used douring a search algoritem on a maze. 
         * @param maze is the maze we tried to solve() 
         * @return soloution::Soloution is the soloution of the maze.(path + value)
         */
        static soloution::Soloution restoreSoloution(const std::vector<statesPair::StatesPair> &pairs, const maze::Maze &maze);

        /**
         * @brief Construct a new Soloution object
         * 
         * @param getPathToSoloution is a string represent the path of the solotion(from the beggining point to teh end.)
         * @param cost is the price we cost to solved the maze based on the values of every state.
         */
        Soloution(const std::string& getPathToSoloution, const uint32_t cost, const uint32_t numberOfVertices, const uint32_t numberOfDevelopedVetices);

        /**
         * @brief Get the Path To Soloution object (the steps we need to do the make it to the end point from the begging point).
         * 
         * @return std::string is represent the path.
         */
        std::string getPathToSoloution() const ;

        /**
         * @brief Get the Cost object(the price we need to pay to solve the maze based on the values of the states.)
         * 
         * @return uint32_t represent the cost.
         */
        uint32_t getCost() const ;

        /**
         * @brief Get the Number Of Vertices object
         * 
         * @return uint32_t is the number of the vertices.
         */
        uint32_t getNumberOfVertices() const;

        /**
         * @brief Get the Number Of Developed Vertices object
         * 
         * @return uint32_t is the number of the developed vertices.
         */
        uint32_t getNumberOfDevelopedVertices() const;
    };
}