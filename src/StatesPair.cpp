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

statesPair::StatesPair::~StatesPair() {
    m_prevState.~MazeState();
    m_curState.~MazeState();
}

void statesPair::StatesPair::set(const statesPair::StatesPair& other) {
    m_curState.set(other.m_curState.getX(), other.m_curState.getY());
    m_prevState.set(other.m_prevState.getX(), other.m_prevState.getY());
}

std::string statesPair::StatesPair::getStepFromPrevToCur() {
   
    if(m_prevState.equlas(m_curState)) {
        return "done.";
    }
    if(m_prevState.getX() +1 == m_curState.getX() && m_prevState.getY() == m_curState.getY()) {
        return "right, ";
    }
    if(m_prevState.getX() -1 == m_curState.getX() && m_prevState.getY() == m_curState.getY()) {
        return "left, ";
    }
    if(m_prevState.getY() +1 == m_curState.getY() && m_prevState.getX() == m_curState.getX()) {
        return "up, ";
    }
    return "down, ";
}