#include "Soloution.hpp"
#include "StatesPair.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <iostream>

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
  uint32_t count = pairs.size() -1;
  auto temp = std::make_unique<statesPair::StatesPair>(pairs.at(count).getPrev(),
                                                       pairs.at(count).getCur());
  while (count != -1) {
        if(pairs.at(count).getCur().equlas(temp->getPrev())) {
            score += maze.getMazeAsMatrix().getValue(temp->getCur().getX(), temp->getCur().getY());
            path += temp->getStepFromPrevToCur();   
            temp->set(pairs.at(count));
            count-=1;
        }
        else {
            count-=1;
        }
    }
    auto soloution = std::make_unique<Soloution>(path, score);
    return *soloution;
}

