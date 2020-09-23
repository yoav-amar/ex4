#include "SearchAlgoritem.hpp"
#include "Maze.hpp"
#include "MazeState.hpp"
#include <memory>
#include <queue>
searchAlgoritem::SearchAlgoritm::SearchAlgoritm(maze::Maze maze)
    : m_maze(maze) {}

searchAlgoritem::BFS_Algoritem::BFS_Algoritem(maze::Maze maze)
    : SearchAlgoritm(maze) {}

maze::Maze searchAlgoritem::SearchAlgoritm::getMaze() { return m_maze; }

void searchAlgoritem::BFS_Algoritem::solve() {
  auto queue = std::make_unique<std::queue<state::MazeState>>();
  auto usedBooths = std::make_unique<std::vector<state::MazeState>>();
  queue->push(m_maze.getstartState());
  while (!queue->empty()) {
    if (queue->front().equlas(m_maze.getEndState())) {
      // we found a path.....do all the important "find path stuff"......
      return;
    }
    auto neighbors = std::make_unique<std::vector<state::MazeState>>(m_maze.getEndState().getAllPossibleNeighbors(m_maze.getMazeAsMatrix()));
    for (int  i = 0; i < neighbors->size(); i ++) {
            queue->push(neighbors->at(i));
    }
    usedBooths->push_back(queue->front());
    queue->pop();
  }
}