#include "Maze.hpp"


namespace searchAlgoritem {
    class SearchAlgoritm {
        protected :
        maze::Maze m_maze;

        public:
        maze::Maze getMaze();
        SearchAlgoritm(maze::Maze maze);
        virtual void solve();
        virtual ~SearchAlgoritm();
    };

    class BFS_Algoritem : public SearchAlgoritm {
        BFS_Algoritem(maze::Maze maze);
        void solve();
    };
}