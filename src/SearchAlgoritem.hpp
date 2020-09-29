#pragma once

#include "Maze.hpp"
#include "MazeState.hpp"
#include "StatesPair.hpp"
#include "Soloution.hpp"

namespace searchAlgoritem {
    class SearchAlgoritm {
        protected :
        maze::Maze m_maze;
        /**
         * @brief check ia a "booth"(like a booth of a maze) has been already visited at the privious levels of the search.
         * 
         * @param booths  is a vector of statesPair that was represent the steps we did at the serach.
         * @param other is a state to check if we alreadt visited at uts.
         * @return true - means we did visit there.
         * @return false - measn we did not visit there.
         */
        static bool boothIsAlreadyVisited(const std::vector<statesPair::StatesPair>& booths, const state::MazeState& other);
        
        public:
        /**
         * @brief Get the Maze object.
         * 
         * @return maze::Maze is the searchAlgoreitem maze field.
         */
        maze::Maze getMaze() const;
        
        /**
         * @brief Construct a new Search Algoritm object.
         * 
         * @param maze is a maze to define as m_maze.
         */
        SearchAlgoritm(const maze::Maze& maze);

        /**
         * @brief solve to maze according to the algoritem (it is a abstract method)
         * 
         * @return soloution::Soloution is the soloution of the maze. 
         */
        virtual soloution::Soloution solve() const = 0;

        /**
         * @brief Destroy the Search Algoritm object
         * 
         */
        virtual ~SearchAlgoritm();
    };

    class BFS_Algoritem : public SearchAlgoritm {

        public:
        /**
         * @brief Construct a new bfs algoritem object
         * 
         * @param maze is a maze to define as m_maze.
         */
        BFS_Algoritem(const maze::Maze& maze);

        /**
         * @brief solve the algoritem with BFS algoritem.
         * 
         * @return soloution::Soloution is the solotion of the maze.
         */
        soloution::Soloution solve() const;

        /**
         * @brief Destroy the bfs algoritem object
         * 
         */
        virtual ~BFS_Algoritem();
    };
    class DFS_Algoritem : public SearchAlgoritm {
      
        public:
        /**
         * @brief Construct a new dfs algoritem object
         * 
         * @param maze is a maze to define as the m_maze.
         */
        DFS_Algoritem(const maze::Maze& maze);

        /**
         * @brief solve the maze with DFS aldoritem.
         * 
         * @return soloution::Soloution is the solotion of the maze.
         */
        virtual soloution::Soloution solve() const ;

        /**
         * @brief Destroy the dfs algoritem object
         * 
         */
        virtual ~DFS_Algoritem();
    };

    class A_STAR_Algoritem : public SearchAlgoritm {
         
         private:
         /**
          * @brief calculate a heuristic value of pair because we need to use it at the A* algoritem.
          * 
          * @param pair 
          * @return double 
          */
         double static heuristicValue(const state::MazeState& state, const maze::Maze& maze);


        public:
        /**
         * @brief Construct a new a star algoritem object.
         * 
         * @param maze is a maze to define as the m_maze.
         */
        A_STAR_Algoritem(const maze::Maze& maze);

        /**
         * @brief solve the maze with A* algoritem.
         * 
         * @return soloution::Soloution is the solotion of the maze.
         */
        virtual soloution::Soloution solve() const ;

        /**
         * @brief Destroy the a star algoritem object
         * 
         */
        virtual ~A_STAR_Algoritem();

    };

    class BestFS_Algoritem : public SearchAlgoritm {
         
         public:
         /**
         * @brief Construct a new a star algoritem object.
         * 
         * @param maze is a maze to define as the m_maze.
         */
        BestFS_Algoritem(const maze::Maze& maze);

        /**
         * @brief solve the maze with A* algoritem.
         * 
         * @return soloution::Soloution is the solotion of the maze.
         */
        virtual soloution::Soloution solve() const ;

        /**
         * @brief Destroy the a star algoritem object
         * 
         */
        virtual ~BestFS_Algoritem();
    };

}