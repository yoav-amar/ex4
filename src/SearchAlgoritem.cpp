#include "SearchAlgoritem.hpp"
#include "Maze.hpp"
#include "MazeState.hpp"
#include "StatesPairTester.hpp"
#include <memory>
#include <queue>
#include <iostream>
#include "Soloution.hpp"

searchAlgoritem::SearchAlgoritm::SearchAlgoritm(maze::Maze maze)
    : m_maze(maze) {}

searchAlgoritem::BFS_Algoritem::BFS_Algoritem(maze::Maze maze)
    : SearchAlgoritm(maze) {}

maze::Maze searchAlgoritem::SearchAlgoritm::getMaze() { return m_maze;}

searchAlgoritem::SearchAlgoritm::~SearchAlgoritm() {
    m_maze.~Maze();
}

searchAlgoritem::BFS_Algoritem::~BFS_Algoritem() {
    m_maze.~Maze();
}



bool searchAlgoritem::BFS_Algoritem::boothIsAlreadyVisited(const std::vector<statesPair::StatesPair>& booths, const state::MazeState& other ) {
    for (int i = 0; i < booths.size(); i ++) {
        if(booths.at(i).getCur().equlas(other)) {
            return true;
        }
    }
    return false;
}

soloution::Soloution searchAlgoritem::BFS_Algoritem::solve() {
  auto queue = std::make_unique<std::queue<statesPair::StatesPair>>();
  auto usedBooths = std::make_unique<std::vector<statesPair::StatesPair>>();
  auto startingBooth = std::make_unique<statesPair::StatesPair>(m_maze.getstartState(), m_maze.getstartState());
  queue->push(*startingBooth);
  while (!queue->empty()) {
      //if we got to the end state find the soloution...
    if (queue->front().getCur().equlas(m_maze.getEndState())) {
        usedBooths->push_back(queue->front());
        return soloution::Soloution::restoreSoloution(*usedBooths, m_maze);
    }
    //if this state is not the end state get all the neighbors of this state to the queue(onlt the one we hasn't visited yet)
    auto neighbors = std::make_unique<std::vector<state::MazeState>>(m_maze.getEndState().getAllPossibleNeighbors(m_maze.getMazeAsMatrix()));
    for (int  i = 0; i < neighbors->size(); i ++) {
        if(!boothIsAlreadyVisited(*usedBooths,neighbors->at(i))) {
        auto pair = std::make_unique<statesPair::StatesPair>(queue->front().getCur(),neighbors->at(i));
        queue->push(*pair);
        }
    }
    //move the top element from the queue to the usedElements vector.
    usedBooths->push_back(queue->front());
    queue->pop();
  }
  auto failureSoloution = std::make_unique<soloution::Soloution>(-1, "no solotion");
  return *failureSoloution;
}