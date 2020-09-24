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
}

void maze::Maze::set(const matrix::Matrix& matrix, const state::MazeState& startState, const state::MazeState& endState) {
    for(int i = 0; i < matrix.getHight(); i++) {
        for(int j = 0; j < matrix.getWidth(); j++) {
            m_mazeAsMatrix.setValue(i , j, matrix.getValue(i,j));
        }
    }
    m_startState.set(startState.getX(), startState.getY());
    m_endState.set(endState.getX(), endState.getY());
}


