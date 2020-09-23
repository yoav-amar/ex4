#include "MazeState.hpp"
#include <cstdint>
#include <vector>
#include "Matrix.hpp"
#include <iostream>
state::MazeState::MazeState(uint32_t x, uint32_t y) {
    m_x = x;
    m_y = y;
}

uint32_t state::MazeState::getX() {
    return m_x;
}

uint32_t state::MazeState::getY() {
    return m_y;
}

std::vector<state::MazeState> state::MazeState::getAllPossibleNeighbors(matrix::Matrix& matrix) {
   std::vector<state::MazeState> neighbors;
    if (( m_x - 1 ) >= 0 && matrix.getValue(m_x - 1, m_y) != -1) {
       auto leftNeighbor = state::MazeState(m_x - 1, m_y);
       neighbors.push_back(leftNeighbor);
    }
    if(m_x + 1 < matrix.getWidth() && matrix.getValue(m_x + 1, m_y) != -1) {
        auto rightNeighbor = state::MazeState(m_x + 1, m_y);
        neighbors.push_back(rightNeighbor);
    }
    if (( m_y - 1 ) >= 0 && matrix.getValue(m_x, m_y - 1) != -1) {
       auto lowerNeighbor = state::MazeState(m_x, m_y - 1);
       neighbors.push_back(lowerNeighbor);
    }
    if(m_y + 1 < matrix.getHight() && matrix.getValue(m_x, m_y + 1) != -1) {
        std::cout<<"flag"<<std::endl;
        auto upperNeighbor = state::MazeState(m_x, m_y + 1);
        neighbors.push_back(upperNeighbor);
    }
    return neighbors;
}