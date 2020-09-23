#include "Maze.hpp"
#include "MazeState.hpp"

maze::Maze::Maze(matrix::Matrix mazeAsMatrix, state::MazeState startState, state::MazeState endState): 
m_mazeAsMatrix(mazeAsMatrix), m_startState(startState.getX(), startState.getY()), m_endState(endState.getX(), endState.getY()) {}

uint32_t maze::Maze::getHeight() const{
    return m_mazeAsMatrix.getHight();
}

uint32_t maze::Maze::getWidth() const{
    return m_mazeAsMatrix.getWidth();
}

matrix::Matrix maze::Maze::getMazeAsMatrix() const{
    auto m = std::make_unique<matrix::Matrix>(m_mazeAsMatrix);
    return *m;
}

state::MazeState maze::Maze::getstartState() const{
    auto s = std::make_unique<state::MazeState>(m_startState.getX(), m_startState.getY());
    return *s;
}

state::MazeState maze::Maze::getEndState() const{
    auto s = std::make_unique<state::MazeState>(m_endState.getX(), m_endState.getY());
    return *s;   
}

maze::Maze::~Maze() {
    m_startState.~MazeState();
    m_endState.~MazeState();
    m_mazeAsMatrix.~Matrix();
}


