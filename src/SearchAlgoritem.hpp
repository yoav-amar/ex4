#pragma once

#include "Maze.hpp"
#include "MazeState.hpp"
#include "StatesPair.hpp"
#include "Soloution.hpp"

namespace searchAlgoritem {
    class SearchAlgoritm {
        protected :
        maze::Maze m_maze;
        static bool boothIsAlreadyVisited(const std::vector<statesPair::StatesPair>& booths, const state::MazeState& other );

        public:
        maze::Maze getMaze();
        SearchAlgoritm(maze::Maze maze);
        virtual soloution::Soloution solve() = 0;
        virtual ~SearchAlgoritm();
    };

    class BFS_Algoritem : public SearchAlgoritm {

        public:
        BFS_Algoritem(maze::Maze maze);
        virtual soloution::Soloution solve();
        virtual ~BFS_Algoritem();
    };
    class DFS_Algoritem : public SearchAlgoritm {
      
        public:
        DFS_Algoritem(maze::Maze maze);
        virtual soloution::Soloution solve();
        virtual ~DFS_Algoritem();
    };

}