#include <vector>

namespace state {
class mazeState {
private:
  int x;
  int y;

public:
  std::vector<mazeState> getAllPossibleNeighbors(maze::Maze maze);
};
} // namespace state