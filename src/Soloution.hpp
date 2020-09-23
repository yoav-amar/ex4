#include <string>
#include <cstdint>
#include "StatesPair.hpp"
#include <vector>
#include "Maze.hpp"
namespace soloution {
    class Soloution {
        private:
        std::string m_pathToSoloution;
        uint32_t m_cost;

        public:
        static soloution::Soloution restoreSoloution(std::vector<statesPair::StatesPair>& pairs, const maze::Maze& maze);
        Soloution(std::string getPathToSoloution, uint32_t cost);
        std::string getPathToSoloution();
        uint32_t getCost();

    };
}