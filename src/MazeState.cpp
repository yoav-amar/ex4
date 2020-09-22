#include "MazeState.hpp"
#include <cstdint>
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
