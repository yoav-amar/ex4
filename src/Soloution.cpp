#include "Soloution.hpp"
#include "StatesPair.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
soloution::Soloution::Soloution(const std::string& path, const uint32_t cost)
    : m_pathToSoloution(path) {
  m_cost = cost;
}

std::string soloution::Soloution::getPathToSoloution() const  {
  std::string s(m_pathToSoloution);
  return s;
}

uint32_t soloution::Soloution::getCost() const { return m_cost; }

/**
 * @brief reversePath-- in the restoreSolotion method below we find the path to the end point but it is not in the right order.
   e.g a solotion path "right up" will be found as "up right" so we need to reverse it.
 * 
 * @param path is the wrong order path.
 * @return std::string is the right order path. 
 */
std::string reversPath(std::string path) {
  std::string newPath;
  if (path.empty()) {
    return "";
  }
  std::vector<std::string> result;
  while (path.size()) {
    int index = path.find(",");
    if (index != std::string::npos) {
      result.push_back(path.substr(0, index));
      path = path.substr(index + std::string(",").size());
      if (path.size() == 0)
        result.push_back(path);
    } else {
      result.push_back(path);
      path = "";
    }
  }
  for (int i = result.size() -1; i > 0; i--) {
    newPath +=  "," + result.at(i);
  }
  return newPath;
}

soloution::Soloution soloution::Soloution::restoreSoloution(
    const std::vector<statesPair::StatesPair> &pairs, const maze::Maze &maze) {
  std::string path("");
  double score = 0;
  if (pairs.size() == 1) {
    auto soloution = std::make_unique<Soloution>(path, score);
    return *soloution;
  }
  uint32_t count = pairs.size() - 1;
  auto temp = std::make_unique<statesPair::StatesPair>(
      pairs.at(count).getPrev(), pairs.at(count).getCur());
  while (count != -1) {
    if (pairs.at(count).getCur().equlas(temp->getPrev())) {
      score += temp->getCur().getValue();
      path += temp->getStepFromPrevToCur();
      temp->set(pairs.at(count));
      count -= 1;
    } else {
      count -= 1;
    }
  }
  auto soloution = std::make_unique<Soloution>(reversPath(path), score);
  return *soloution;
}
