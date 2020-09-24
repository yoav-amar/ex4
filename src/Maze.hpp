#pragma once
#include "Matrix.hpp"
#include "MazeState.hpp"
#include <cstdint>
namespace maze {
    class Maze {
        private:
        matrix::Matrix m_mazeAsMatrix;
        state::MazeState m_startState;
        state::MazeState m_endState;

        public:
        /**
         * @brief Construct a new Maze object.
         * 
         * @param matrix is a matrix that represent the maze.
         * @param startState is the start State of the maze.
         * @param endState is the end State of the maze.
         */
        Maze(matrix::Matrix matrix, state::MazeState startState, state::MazeState endState);
        
        /**
         * @brief Get the Width of the matrix that represent the maze.
         * 
         * @return uint32_t - the width of the maze.
         */
        uint32_t getWidth() const;
        /**
         * @brief Get the Height of the maztrix that represent the maze.
         * 
         * @return uint32_t - the height of the matrix.
         */
        uint32_t getHeight() const;
        
        /**
         * @brief Get the Matrix that represent the maze.
         * 
         * @return matrix::Matrix - a mztrix that represent the maze.
         */
        matrix::Matrix getMazeAsMatrix() const;
        
        /**
         * @brief get the start state of this maze.
         * 
         * @return state::MazeState - the start state of this maze.
         */
        state::MazeState getstartState() const;
        
        /**
         * @brief Get the end state of this matrix.
         * 
         * @return state::MazeState - the end state of this matrix.
         */
        state::MazeState getEndState() const ;

        /**
         * @brief Destroy the Maze object
         * 
         */
         ~Maze();

        /**
         * @brief set thhis object.
         * 
         */
         void set(const matrix::Matrix& matrix, const state::MazeState& startState, const state::MazeState& endState);

    };
}