#include "SearchAlgoritem.hpp"
#include "Maze.hpp"
#include "MazeState.hpp"
#include "Soloution.hpp"
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
  return std::abs((int)state.getX() - (int)maze.getEndState().getX()) +
         std::abs((int)state.getY() - (int)maze.getEndState().getY());
}

bool searchAlgoritem::SearchAlgoritm::boothIsAlreadyVisited(
    const std::vector<statesPair::StatesPair> &booths,
    const state::MazeState &other) {
      for (int i = 0; i < booths.size(); ++i) {
              //  std::cout<<booths.at(i).getCur().getX()<<","<<booths.at(i).getCur().getY()<<"|"<<other.getX()<<","<<other.getY()<<std::endl;
          if (booths.at(i).getCur().equlas(other)) {
              //  std::cout<<"cap";
               return true;
          }
      }
      return false;
  }

soloution::Soloution searchAlgoritem::BFS_Algoritem::solve() const {
  auto endPoint = std::make_unique<state::MazeState>(m_maze.getEndState().getX(), m_maze.getEndState().getY(), m_maze.getEndState().getValue());
  auto mazeAsMatrix = std::make_unique<matrix::Matrix>(m_maze.getMazeAsMatrix());
  auto usedBooths = std::make_unique<std::vector<statesPair::StatesPair>>();
  auto queue =std::make_unique<std::queue<statesPair::StatesPair>>();
  auto startingBooth = std::make_unique<statesPair::StatesPair>(m_maze.getstartState(), m_maze.getstartState());
  usedBooths->push_back(*startingBooth);
  queue->push(*startingBooth);

  while(!queue->empty()) {
    auto top = std::make_unique<statesPair::StatesPair>(queue->front().getPrev(), queue->front().getCur());
    auto top_cur = std::make_unique<state::MazeState>(queue->front().getCur().getX(), queue->front().getCur().getY(), queue->front().getCur().getValue());
    if(top_cur->equlas(*endPoint)) {
      return soloution::Soloution::restoreSoloution(*usedBooths, m_maze);
    }
    queue->pop();
    auto neighbors = std::make_unique<std::vector<state::MazeState>>(top_cur->getAllPossibleNeighbors(*mazeAsMatrix));
    for(int i = 0; i < neighbors->size(); ++i) {
      if(!boothIsAlreadyVisited(*usedBooths, neighbors->at(i))) {
        auto pair = std::make_unique<statesPair::StatesPair>(*top_cur, neighbors->at(i));
        usedBooths->push_back(*pair);
        queue->push(*pair);
      }
    }
  }
  auto failureSoloution =
      std::make_unique<soloution::Soloution>("no solotion", 0, 0, 0);
  return *failureSoloution;
}

soloution::Soloution searchAlgoritem::DFS_Algoritem::solve() const {
  auto mazeAsMatrix = std::make_unique<matrix::Matrix>(m_maze.getMazeAsMatrix());
  auto stack = std::make_unique<std::stack<statesPair::StatesPair>>();
  auto usedBooths = std::make_unique<std::vector<statesPair::StatesPair>>();
  auto startingBooth = std::make_unique<statesPair::StatesPair>(
      m_maze.getstartState(), m_maze.getstartState());
      usedBooths->push_back(*startingBooth);
  stack->push(*startingBooth);
  while (!stack->empty()) {
    auto top = std::make_unique<statesPair::StatesPair>(stack->top());
    auto top_cur = std::make_unique<state::MazeState>(top->getCur());
    //   // if we got to the end state find the soloution...
    if (top_cur->equlas(m_maze.getEndState())) {
      return soloution::Soloution::restoreSoloution(*usedBooths, m_maze);
    }
    //   // if this state is not the end state get all the neighbors of this
    //   state to
    //   // the queue(onlt the one we hasn't visited yet)
    auto neighbors = std::make_unique<std::vector<state::MazeState>>(
        top_cur->getAllPossibleNeighbors(
            *mazeAsMatrix));
    //   // move the top element from the queue to the usedElements vector.
    stack->pop();
    for (int i = 0; i < neighbors->size(); i++) {
      if (!boothIsAlreadyVisited(*usedBooths, neighbors->at(i))) {
        auto pair =
            std::make_unique<statesPair::StatesPair>(*top_cur, neighbors->at(i));
            usedBooths->push_back(*pair);
        stack->push(*pair);
      }
    }
  }
  auto failureSoloution =
      std::make_unique<soloution::Soloution>("no solotion", 0, 0, 0);
  return *failureSoloution;
}

// bad design has forced me to write this weird thing, im sorry...
// https://www.youtube.com/watch?v=3tmd-ClpJxA
soloution::Soloution searchAlgoritem::A_STAR_Algoritem::solve() const {
  auto mazeAsMatrix = std::make_unique<matrix::Matrix>(m_maze.getMazeAsMatrix());
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
      heuristic_value);
  auto heuristic_startingBooth = std::make_unique<statesPair::StatesPair>(
      *heuristic_startState, *heuristic_startState);

  priorityQueue->push(*heuristic_startingBooth);
  usedBooths->push_back(*startingBooth);
  while (!priorityQueue->empty()) {
    auto top = std::make_unique<statesPair::StatesPair>(priorityQueue->top());
    auto top_cur = std::make_unique<state::MazeState>(top->getCur());
    auto regular_cur = std::make_unique<state::MazeState>(
        priorityQueue->top().getCur().getX(),
        priorityQueue->top().getCur().getY(),
        priorityQueue->top().getCur().getValue() -
            heuristicValue(priorityQueue->top().getCur(), m_maze));
    //   // if we got to the end state find the soloution...
    if (regular_cur->equlas(m_maze.getEndState())) {
      return soloution::Soloution::restoreSoloution(*usedBooths, m_maze);
    }
    //   // if this state is not the end state get all the neighbors of this
    //   state to
    //   // the queue(onlt the one we hasn't visited yet)
    auto neighbors = std::make_unique<std::vector<state::MazeState>>(
        regular_cur->getAllPossibleNeighbors(
            *mazeAsMatrix));
    //   // move the top element from the queue to the usedElements vector.
    auto regular_pair = std::make_unique<statesPair::StatesPair>(
        priorityQueue->top().getPrev(), *regular_cur);
    usedBooths->push_back(*regular_pair);
    priorityQueue->pop();

    for (int i = 0; i < neighbors->size(); i++) {
      auto heuristic_neighbor = std::make_unique<state::MazeState>(
          neighbors->at(i).getX(), neighbors->at(i).getY(),
          neighbors->at(i).getValue() +
              heuristicValue(neighbors->at(i), m_maze));
      if (!boothIsAlreadyVisited(*usedBooths, *heuristic_neighbor)) {
        auto heuristic_pair = std::make_unique<statesPair::StatesPair>(
            *top_cur, *heuristic_neighbor);
        auto regular_pair = std::make_unique<statesPair::StatesPair>(*regular_cur, neighbors->at(i));
        priorityQueue->push(*heuristic_pair);
        usedBooths->push_back(*regular_pair);
      }
    }
  }
  auto failureSoloution =
      std::make_unique<soloution::Soloution>("no solotion", 0, 0, 0);
  return *failureSoloution;
}

soloution::Soloution searchAlgoritem::BestFS_Algoritem::solve() const {
  auto mazeAsMatrix = std::make_unique<matrix::Matrix>(m_maze.getMazeAsMatrix());
  auto priorityQueue = std::make_unique<std::priority_queue<
      statesPair::StatesPair, std::vector<statesPair::StatesPair>,
      statesPair::StatesPair::pairComparator>>();
  auto usedBooths = std::make_unique<std::vector<statesPair::StatesPair>>();
  auto startingBooth = std::make_unique<statesPair::StatesPair>(
      m_maze.getstartState(), m_maze.getstartState());

  priorityQueue->push(*startingBooth);
  usedBooths->push_back(*startingBooth);

  while (!priorityQueue->empty()) {
    auto top = std::make_unique<statesPair::StatesPair>(priorityQueue->top());
    auto top_cur = std::make_unique<state::MazeState>(top->getCur());
    // if we got to the end state find the soloution...
    if (top_cur->equlas(m_maze.getEndState())) {
      return soloution::Soloution::restoreSoloution(*usedBooths, m_maze);
    }
    // if this state is not the end state get all the neighbors of this state to
    // the queue(onlt the one we hasn't visited yet)
    auto neighbors = std::make_unique<std::vector<state::MazeState>>(
        top_cur->getAllPossibleNeighbors(
           *mazeAsMatrix));
    // move the top element from the queue to the usedElements vector.
    priorityQueue->pop();
    for (int i = 0; i < neighbors->size(); i++) {
      if (!boothIsAlreadyVisited(*usedBooths, neighbors->at(i))) {
        auto pair =
            std::make_unique<statesPair::StatesPair>(*top_cur, neighbors->at(i));
            usedBooths->push_back(*pair);
        priorityQueue->push(*pair);
      }
    }
  }
  auto failureSoloution =
      std::make_unique<soloution::Soloution>("no solotion", 0, 0, 0);
  return *failureSoloution;
}