#pragma once
#include <vector>
#include <cstdint>
#include "Matrix.hpp"
#include <memory>
namespace state {
class MazeState {
private:
  uint32_t m_x;
  uint32_t m_y;

public:

/**
 * @brief Construct a new Maze State object.
 * 
 * @param x is an integer.
 * @param y is an integer.
 */
  MazeState(const uint32_t x, const uint32_t y);
  /**
   * @brief return the x position of this state.
   *
   * @return int
   */
  uint32_t getX() const;

  /**
   * @brief return the y position of this state.
   *
   * @return int
   */
  uint32_t getY() const;

  /**
   * @brief Get the All Possible Neighbors (as a vector of states) of this state
   * by a given maze.
   *
   * @param matrix is a mmatrix of a maze that the state represnt a boot on it.
   * @return std::vector<mazeState> is a vector of all the neighbors boots ofget
   * the boot that represent this state on the maze.
   */
  std::vector<state::MazeState> getAllPossibleNeighbors(const matrix::Matrix& matrix) const;

  bool equlas(const state::MazeState& state) const;
  
  void set(const uint32_t x, const uint32_t y);

  ~MazeState();

};
} // namespace state