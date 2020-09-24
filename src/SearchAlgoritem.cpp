#include "SearchAlgoritem.hpp"
#include "Maze.hpp"
#include "MazeState.hpp"
#include "Soloution.hpp"
#include "StatesPairTester.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <stack>
#include "PairAndPrice.hpp"

searchAlgoritem::SearchAlgoritm::SearchAlgoritm(maze::Maze maze)
    : m_maze(maze) {}

searchAlgoritem::BFS_Algoritem::BFS_Algoritem(maze::Maze maze)
    : SearchAlgoritm(maze) {}

searchAlgoritem::DFS_Algoritem::DFS_Algoritem(maze::Maze maze)
    : SearchAlgoritm(maze) {}

maze::Maze searchAlgoritem::SearchAlgoritm::getMaze() { return m_maze; }

searchAlgoritem::SearchAlgoritm::~SearchAlgoritm() = default;

searchAlgoritem::BFS_Algoritem::~BFS_Algoritem() = default;

searchAlgoritem::DFS_Algoritem::~DFS_Algoritem() = default;

searchAlgoritem::A_STAR_Algoritem::A_STAR_Algoritem(maze::Maze maze)
    : SearchAlgoritm(maze) {}

searchAlgoritem::A_STAR_Algoritem::~A_STAR_Algoritem() = default;

maze::Maze searchAlgoritem::SearchAlgoritm::getMaze() {
    return m_maze;
}

double searchAlgoritem::SearchAlgoritm::heuristicValue(const statesPair::StatesPair& pair) {
  return std::abs(pair.getCur().getX() - m_maze.getEndState().getX()) +
         std::abs(pair.getCur().getY() - m_maze.getEndState().getY()) +
         m_maze.getMazeAsMatrix().getValue(pair.getCur().getX(),
                                         pair.getCur().getY());
}


bool searchAlgoritem::SearchAlgoritm::boothIsAlreadyVisited(
    const std::vector<statesPair::StatesPair> &booths,
    const state::MazeState &other) {
  for (int i = 0; i < booths.size(); i++) {
    if (booths.at(i).getCur().equlas(other)) {
      return true;
    }
  }
  return false;
}

soloution::Soloution searchAlgoritem::BFS_Algoritem::solve() {
  auto queue = std::make_unique<std::queue<statesPair::StatesPair>>();
  auto usedBooths = std::make_unique<std::vector<statesPair::StatesPair>>();
  auto startingBooth = std::make_unique<statesPair::StatesPair>(
      m_maze.getstartState(), m_maze.getstartState());
  queue->push(*startingBooth);
  while (!queue->empty()) {
    // if we got to the end state find the soloution...
    if (queue->front().getCur().equlas(m_maze.getEndState())) {
      usedBooths->push_back(queue->front());
      return soloution::Soloution::restoreSoloution(*usedBooths, m_maze);
    }
    // if this state is not the end state get all the neighbors of this state to
    // the queue(onlt the one we hasn't visited yet)
    auto neighbors = std::make_unique<std::vector<state::MazeState>>(
        queue->front().getCur().getAllPossibleNeighbors(
            m_maze.getMazeAsMatrix()));
    for (int i = 0; i < neighbors->size(); i++) {
      if (!boothIsAlreadyVisited(*usedBooths, neighbors->at(i))) {
        auto pair = std::make_unique<statesPair::StatesPair>(
            queue->front().getCur(), neighbors->at(i));
        queue->push(*pair);
      }
    }
    // move the top element from the queue to the usedElements vector.
    usedBooths->push_back(queue->front());
    queue->pop();
  }
  auto failureSoloution =
      std::make_unique<soloution::Soloution>("no solotion", 0);
  return *failureSoloution;
}

soloution::Soloution searchAlgoritem::DFS_Algoritem::solve() {
  auto stack = std::make_unique<std::stack<statesPair::StatesPair>>();
  auto usedBooths = std::make_unique<std::vector<statesPair::StatesPair>>();
  auto startingBooth = std::make_unique<statesPair::StatesPair>(
      m_maze.getstartState(), m_maze.getstartState());
  stack->push(*startingBooth);
  while (!stack->empty()) {
    // if we got to the end state find the soloution...
    if (stack->top().getCur().equlas(m_maze.getEndState())) {
      usedBooths->push_back(stack->top());
      return soloution::Soloution::restoreSoloution(*usedBooths, m_maze);
    }
    // if this state is not the end state get all the neighbors of this state to
    // the queue(onlt the one we hasn't visited yet)
    auto neighbors = std::make_unique<std::vector<state::MazeState>>(
        stack->top().getCur().getAllPossibleNeighbors(
            m_maze.getMazeAsMatrix()));
    // move the top element from the queue to the usedElements vector.
    usedBooths->push_back(stack->top());
    stack->pop();
    for (int i = 0; i < neighbors->size(); i++) {
      if (!boothIsAlreadyVisited(*usedBooths, neighbors->at(i))) {
        auto pair = std::make_unique<statesPair::StatesPair>(
            stack->top().getCur(), neighbors->at(i));
        stack->push(*pair);
      }
    }
  }
  auto failureSoloution =
      std::make_unique<soloution::Soloution>("no solotion", 0);
  return *failureSoloution;
}

statesPair::StatesPair searchAlgoritem::SearchAlgoritm::get_min(std::vector<pairAndPrice::PairAndPrice>& vec) {
    double maxValue = vec[0].getPrice();
    uint32_t maxIdx = 0;
    for(int  i = 0; i < vec.size(); ++i) {
        if(vec[i].getPrice() > vec[maxIdx].getPrice()) {
            maxIdx = i;
            maxValue = vec[i].getPrice();
        }
    }
    return vec[maxIdx].getPair();
}


//bad design has forced me to write this weird thing, im sorry...  https://www.youtube.com/watch?v=3tmd-ClpJxA
soloution::Soloution searchAlgoritem::A_STAR_Algoritem::solve() {
  auto map = std::make_unique<std::vector<pairAndPrice::PairAndPrice>>();
  auto usedBooths = std::make_unique<std::vector<statesPair::StatesPair>>();
  auto startingBooth = std::make_unique<statesPair::StatesPair>(
      m_maze.getstartState(), m_maze.getstartState());
      double price = heuristicValue(*startingBooth);
    map->push_back(pairAndPrice::PairAndPrice(*startingBooth, price));
  while (!map->empty()) {
    // if we got to the end state find the soloution...
    if (get_min(*map).getCur().equlas(m_maze.getEndState())) {
      usedBooths->push_back(map->top());
      return soloution::Soloution::restoreSoloution(*usedBooths, m_maze);
    }
    // if this state is not the end state get all the neighbors of this state to
    // the queue(onlt the one we hasn't visited yet)
    auto neighbors = std::make_unique<std::vector<state::MazeState>>(
        map->top().getCur().getAllPossibleNeighbors(m_maze.getMazeAsMatrix()));
    // move the top element from the queue to the usedElements vector.
    usedBooths->push_back(map->top());
    map->pop();
    for (int i = 0; i < neighbors->size(); i++) {
      if (!boothIsAlreadyVisited(*usedBooths, neighbors->at(i))) {
        auto pair = std::make_unique<statesPair::StatesPair>(
            map->top().getCur(), neighbors->at(i));
        map->push(*pair);
      }
    }
  }
  auto failureSoloution =
      std::make_unique<soloution::Soloution>("no solotion", 0);
  return *failureSoloution;
}