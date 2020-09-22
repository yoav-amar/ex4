#include <vector>

namespace state {
class mazeState {
private:
  int x;
  int y;

public:
  /**
   * @brief return the x position of this state.
   *
   * @return int
   */
  int getX();

  /**
   * @brief return the y position of this state.
   *
   * @return int
   */
  int getY();

  /**
   * @brief Get the All Possible Neighbors (as a vector of states) of this state
   * by a given maze.
   *
   * @param maze is a maze to that the state represnt a boot on it.
   * @return std::vector<mazeState> is a vector of all the neighbors boots of
   * the boot that represent this state on the maze.
   */
  std::vector<mazeState> getAllPossibleNeighbors(maze::Maze maze);
};
} // namespace state