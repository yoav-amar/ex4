#pragma once

#include "Maze.hpp"
#include "MazeState.hpp"
#include "StatesPair.hpp"

namespace searchAlgoritem {
    class SearchAlgoritm {
        protected :
        maze::Maze m_maze;

        public:
        maze::Maze getMaze();
        SearchAlgoritm(maze::Maze maze);
        virtual void solve();
         ~SearchAlgoritm();
    };

    class BFS_Algoritem : public SearchAlgoritm {
        private:
        static bool boothIsAlreadyVisited(const std::vector<statesPair::StatesPair>& booths, const state::MazeState& other );
        
        public:
        BFS_Algoritem(maze::Maze maze);
        virtual void solve();
         ~BFS_Algoritem();
    };
}