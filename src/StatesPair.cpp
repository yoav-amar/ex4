#include "StatesPair.hpp"
#include "MazeState.hpp"
#include <memory>

statesPair::StatesPair::StatesPair(const state::MazeState &prev,
                                   const state::MazeState &cur)
    : m_prevState(prev.getX(), prev.getY(), prev.getValue()),
      m_curState(cur.getX(), cur.getY(), cur.getValue()) {}

state::MazeState statesPair::StatesPair::getCur() const {
  auto state = std::make_unique<state::MazeState>(
      m_curState.getX(), m_curState.getY(), m_curState.getValue());
  return *state;
}

state::MazeState statesPair::StatesPair::getPrev() const {
  auto state = std::make_unique<state::MazeState>(
      m_prevState.getX(), m_prevState.getY(), m_prevState.getValue());
  return *state;
}

statesPair::StatesPair::~StatesPair() {
  m_prevState.~MazeState();
  m_curState.~MazeState();
}

void statesPair::StatesPair::set(const statesPair::StatesPair &other) {
  m_curState.set(other.getCur().getX(), other.getCur().getY(),
                 other.getCur().getValue());
  m_prevState.set(other.getPrev().getX(), other.getPrev().getY(),
                  other.getPrev().getValue());
}

std::string statesPair::StatesPair::getStepFromPrevToCur() const {

  if (m_prevState.equlas(m_curState)) {
    return "";
  }
  if (m_prevState.getX() + 1 == m_curState.getX() &&
      m_prevState.getY() == m_curState.getY()) {
    return ",Right";
  }
  if (m_prevState.getX() - 1 == m_curState.getX() &&
      m_prevState.getY() == m_curState.getY()) {
    return ",Left";
  }
  if (m_prevState.getY() + 1 == m_curState.getY() &&
      m_prevState.getX() == m_curState.getX()) {
    return ",Up";
  }
  return ",Down";
}

bool statesPair::StatesPair::operator!=(const statesPair::StatesPair& other) {
    return  m_curState.getValue() != other.getCur().getValue();
}

bool statesPair::StatesPair::operator==(const statesPair::StatesPair& other) {
    return  m_curState.getValue() == other.getCur().getValue();
}

bool statesPair::StatesPair::operator<=(const statesPair::StatesPair& other) {
    return  m_curState.getValue() <= other.getCur().getValue();
}

bool statesPair::StatesPair::operator>=(const statesPair::StatesPair& other) {
    return  m_curState.getValue() >= other.getCur().getValue();
}

bool statesPair::StatesPair::operator<(const statesPair::StatesPair& other) {
    return  m_curState.getValue() < other.getCur().getValue();
}

bool statesPair::StatesPair::operator>(const statesPair::StatesPair& other) {
    return  m_curState.getValue() > other.getCur().getValue();
}

bool statesPair::StatesPair::pairComparator::operator() (const statesPair::StatesPair& pair1, const statesPair::StatesPair& pair2) {
      return pair1.getCur().getValue() < pair2.getCur().getValue();
}
