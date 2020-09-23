#pragma once

#include "MazeState.hpp"
#include<cstdint>
namespace statesPair {
    class StatesPair {
        private:
        state::MazeState m_curState;
        state::MazeState m_prevState;

        public:
        StatesPair(const state::MazeState cur, const state::MazeState prev);
        state::MazeState getPrev() const;
        state::MazeState getCur() const;
        ~StatesPair();
    };
}