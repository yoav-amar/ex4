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

searchAlgoritem::SearchAlgoritm::SearchAlgoritm(const maze::Maze &maze)
    : m_maze(maze.getMazeAsMatrix(), maze.getstartState(), maze.getEndState()) {
}

searchAlgoritem::BFS_Algoritem::BFS_Algoritem(const maze::Maze &maze)
    : SearchAlgoritm(maze) {}

searchAlgoritem::DFS_Algoritem::DFS_Algoritem(const maze::Maze &maze)
    : SearchAlgoritm(maze) {}

searchAlgoritem::A_STAR_Algoritem::A_STAR_Algoritem(const maze::Maze &maze)
    : SearchAlgoritm(maze) {}

searchAlgoritem::BestFS_Algoritem::BestFS_Algoritem(const maze::Maze &maze)
    : SearchAlgoritm(maze) {}

maze::Maze searchAlgoritem::SearchAlgoritm::getMaze() const {
  auto mazeCopy = std::make_unique<maze::Maze>(
      m_maze.getMazeAsMatrix(), m_maze.getstartState(), m_maze.getEndState());
  return *mazeCopy;
}

searchAlgoritem::SearchAlgoritm::~SearchAlgoritm() = default;

searchAlgoritem::BFS_Algoritem::~BFS_Algoritem() = default;

searchAlgoritem::DFS_Algoritem::~DFS_Algoritem() = default;

searchAlgoritem::A_STAR_Algoritem::~A_STAR_Algoritem() = default;

searchAlgoritem::BestFS_Algoritem::~BestFS_Algoritem() = default;

double
searchAlgoritem::A_STAR_Algoritem::heuristicValue(const state::MazeState &state,
                                                  const maze::Maze &maze) {
  return std::abs(state.getX() - maze.getEndState().getX()) +
         std::abs(state.getY() - maze.getEndState().getY());
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

soloution::Soloution searchAlgoritem::BFS_Algoritem::solve() const {
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

soloution::Soloution searchAlgoritem::DFS_Algoritem::solve() const {
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

// statesPair::StatesPair
// searchAlgoritem::SearchAlgoritm::get_min(std::vector<pairAndPrice::PairAndPrice>&
// vec) {
//     double maxValue = vec[0].getPrice();
//     uint32_t maxIdx = 0;
//     for(int  i = 0; i < vec.size(); ++i) {
//         if(vec[i].getPrice() > vec[maxIdx].getPrice()) {
//             maxIdx = i;
//             maxValue = vec[i].getPrice();
//         }
//     }
//     return vec[maxIdx].getPair();
// }

// bad design has forced me to write this weird thing, im sorry...
// https://www.youtube.com/watch?v=3tmd-ClpJxA
soloution::Soloution searchAlgoritem::A_STAR_Algoritem::solve() const {
  auto priorityQueue = std::make_unique<std::priority_queue<
      statesPair::StatesPair, std::vector<statesPair::StatesPair>,
      statesPair::StatesPair::pairComparator>>();
  auto usedBooths = std::make_unique<std::vector<statesPair::StatesPair>>();
  auto startingBooth = std::make_unique<statesPair::StatesPair>(
      m_maze.getstartState(), m_maze.getstartState());
  double heuristic_value = startingBooth->getCur().getValue() +
                           heuristicValue(startingBooth->getCur(), m_maze);
  auto heuristic_startState = std::make_unique<state::MazeState>(
      startingBooth->getCur().getX(), startingBooth->getCur().getY(),
      heuristicValue);
  auto heuristic_startingBooth = std::make_unique<statesPair::StatesPair>(
      *heuristic_startState, *heuristic_startState);

  priorityQueue->push(*heuristic_startingBooth);

  while (!priorityQueue->empty()) {
    // if we got to the end state find the soloution...
    if (priorityQueue->top().getCur().equlas(m_maze.getEndState())) {
      auto regular_pair = std::make_unique<statesPair::StatesPair>(priorityQueue->top().getPrev(), priorityQueue->top().getCur(), priorityQueue->top().getCur().getValue()- heuristicValue(priorityQueue->top().getCur(), m_maze));
      usedBooths->push_back(*regular_pair);
      return soloution::Soloution::restoreSoloution(*usedBooths, m_maze);
    }
    // if this state is not the end state get all the neighbors of this state to
    // the queue(onlt the one we hasn't visited yet)
    auto neighbors = std::make_unique<std::vector<state::MazeState>>(
        priorityQueue->top().getCur().getAllPossibleNeighbors(
            m_maze.getMazeAsMatrix()));
    // move the top element from the queue to the usedElements vector.
    usedBooths->push_back(priorityQueue->top());
    priorityQueue->pop();
    for (int i = 0; i < neighbors->size(); i++) {
      auto heuristic_neighbor = std::make_unique<state::MazeState>(
          neighbors->at(i).getX(), neighbors->at(i).getY(),
          neighbors->at(i).getValue() +
              heuristicValue(neighbors->at(i), m_maze));
      if (!boothIsAlreadyVisited(*usedBooths, *heuristic_neighbor)) {
        auto pair = std::make_unique<statesPair::StatesPair>(
            priorityQueue->top().getCur(), *heuristic_neighbor);
        priorityQueue->push(*pair);
      }
    }
  }
  auto failureSoloution =
      std::make_unique<soloution::Soloution>("no solotion", 0);
  return *failureSoloution;
}

soloution::Soloution searchAlgoritem::BestFS_Algoritem::solve() const {
  auto priorityQueue = std::make_unique<std::priority_queue<
      statesPair::StatesPair, std::vector<statesPair::StatesPair>,
      statesPair::StatesPair::pairComparator>>();
  auto usedBooths = std::make_unique<std::vector<statesPair::StatesPair>>();
  auto startingBooth = std::make_unique<statesPair::StatesPair>(
      m_maze.getstartState(), m_maze.getstartState());

  priorityQueue->push(*startingBooth);

  while (!priorityQueue->empty()) {
    // if we got to the end state find the soloution...
    if (priorityQueue->top().getCur().equlas(m_maze.getEndState())) {
      usedBooths->push_back(priorityQueue->top());
      return soloution::Soloution::restoreSoloution(*usedBooths, m_maze);
    }
    // if this state is not the end state get all the neighbors of this state to
    // the queue(onlt the one we hasn't visited yet)
    auto neighbors = std::make_unique<std::vector<state::MazeState>>(
        priorityQueue->top().getCur().getAllPossibleNeighbors(
            m_maze.getMazeAsMatrix()));
    // move the top element from the queue to the usedElements vector.
    usedBooths->push_back(priorityQueue->top());
    priorityQueue->pop();
    for (int i = 0; i < neighbors->size(); i++) {
      if (!boothIsAlreadyVisited(*usedBooths, neighbors->at(i))) {
        auto pair = std::make_unique<statesPair::StatesPair>(
            priorityQueue->top().getCur(), neighbors->at(i));
        priorityQueue->push(*pair);
      }
    }
  }
  auto failureSoloution =
      std::make_unique<soloution::Soloution>("no solotion", 0);
  return *failureSoloution;
}