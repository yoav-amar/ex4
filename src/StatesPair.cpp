#include "StatesPair.hpp"
#include <memory>
#include "MazeState.hpp"

statesPair::StatesPair::StatesPair(state::MazeState prev, state::MazeState cur) :
m_prevState(prev.getX(), prev.getY()), m_curState(cur.getX(), cur.getY()) {}

state::MazeState statesPair::StatesPair::getCur() const{
    auto state = std::make_unique<state::MazeState>(m_curState.getX(), m_curState.getY());
    return *state;
}

state::MazeState statesPair::StatesPair::getPrev() const{
     auto state = std::make_unique<state::MazeState>(m_prevState.getX(), m_prevState.getY());
     return *state;
}

