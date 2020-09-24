#include "MazeState.hpp"
#include <cstdint>
#include <vector>
#include "Matrix.hpp"
#include <iostream>
state::MazeState::MazeState(const uint32_t x, const uint32_t y) {
    m_x = x;
    m_y = y;
}

uint32_t state::MazeState::getX() const {
    return m_x;
}

uint32_t state::MazeState::getY() const {
    return m_y;
}

std::vector<state::MazeState> state::MazeState::getAllPossibleNeighbors(const matrix::Matrix& matrix) const {
   std::vector<state::MazeState> neighbors;
    if ((m_x != 0) && (matrix.getValue(m_x - 1, m_y) != -1) ) {
       auto leftNeighbor = state::MazeState(m_x - 1, m_y);
       neighbors.push_back(leftNeighbor);
    }
    if((m_x != matrix.getWidth() - 1) && (matrix.getValue(m_x + 1, m_y) != -1)) {
        auto rightNeighbor = state::MazeState(m_x + 1, m_y);
        neighbors.push_back(rightNeighbor); 
    }
    if ((m_y != 0) && (matrix.getValue(m_x, m_y-1) != -1)) {
       auto lowerNeighbor = state::MazeState(m_x, m_y - 1);
       neighbors.push_back(lowerNeighbor);
    }
    if((m_y != matrix.getWidth() -1) && (matrix.getValue(m_x, m_y + 1))) {
        auto upperNeighbor = state::MazeState(m_x, m_y + 1);
        neighbors.push_back(upperNeighbor);
    }
    return neighbors;
}

bool state::MazeState::equlas(const state::MazeState& other ) const {
    if (other.getX() == m_x && other.getY() == m_y) {
        return true;
    }
    return false;
}

void state::MazeState::set(const uint32_t x, const uint32_t y) {
    m_x = x;
    m_y = y;
}

state::MazeState::~MazeState() = default;