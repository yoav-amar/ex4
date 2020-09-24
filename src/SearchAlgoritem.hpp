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
        double heuristicValue(const statesPair::StatesPair& pair);

        public:
        maze::Maze getMaze();
        SearchAlgoritm(maze::Maze maze);
        virtual soloution::Soloution solve() = 0;
        virtual ~SearchAlgoritm();
        static statesPair::StatesPair get_min(std::vector<pairAndPrice::PairAndPrice>& vec);
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

    class A_STAR_Algoritem : public SearchAlgoritm {


        public:
        A_STAR_Algoritem(maze::Maze maze);
        virtual soloution::Soloution solve();
        virtual ~A_STAR_Algoritem();

    };

}