#include "Soloution.hpp"
#include "StatesPair.hpp"
#include <cstdint>
#include <memory>
#include <string>

soloution::Soloution::Soloution(std::string path, uint32_t cost)
    : m_pathToSoloution(path) {
  m_cost = cost;
}

std::string soloution::Soloution::getPathToSoloution() {
  std::string s(m_pathToSoloution);
  return s;
}

uint32_t soloution::Soloution::getCost() { return m_cost; }

soloution::Soloution soloution::Soloution::restoreSoloution(
    std::vector<statesPair::StatesPair> &pairs, const maze::Maze &maze) {
  std::string path("");
  double score = 0;
  if (pairs.size() == 1) {
    auto soloution = std::make_unique<Soloution>(path, score);
    return *soloution;
  }
  auto temp = std::make_unique<statesPair::StatesPair>(pairs.front().getPrev(),
                                                       pairs.front().getCur());
  while (!pairs.empty()) {
    if (pairs.front().getCur().equlas(temp->getPrev())) {
      score += maze.getMazeAsMatrix().getValue(temp->getCur().getX(),
                                               temp->getCur().getY());
      path += temp->getStepFromPrevToCur();
      temp->set(pairs.front());
      pairs.pop_back();
    } else {
      pairs.pop_back();
    }
  }
  auto soloution = std::make_unique<Soloution>(path, score);
  return *soloution;
}
