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
  double m_value;

public:

/**
 * @brief Construct a new Maze State object.
 * 
 * @param x is an integer.
 * @param y is an integer.
 */
  MazeState(const uint32_t x, const uint32_t y, const double value);
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
   * @brief Get the Value of the stste
   * 
   * @return double - the value of the state.
   */
  double getValue() const;


  /**
   * @brief Get the All Possible Neighbors (as a vector of states) of this state
   * by a given maze.
   *
   * @param matrix is a mmatrix of a maze that the state represnt a boot on it.
   * @return std::vector<mazeState> is a vector of all the neighbors boots ofget
   * the boot that represent this state on the maze.
   */
  std::vector<state::MazeState> getAllPossibleNeighbors(const matrix::Matrix& matrix) const;


  /**
   * @brief check if other state is equal to this state.
     equal means that the have the same x , y and value.
   * 
   * @param state is the other state to check if equal.
   * @return true - means they are equal
   * @return false  - means they are not equal.
   */
  bool equlas(const state::MazeState& state) const;
  
  /**
   * @brief set the values of the fields.
   * 
   * @param value is a double varriabke to set m_value
   * @param x is an integer varriale to set m_x
   * @param y is an integer varriale to set m_y
   */
  void set(const uint32_t x, const uint32_t y, double value);

  /**
  * @brief Destroy the Maze State object.
  * 
  */
  ~MazeState();

};
} // namespace state