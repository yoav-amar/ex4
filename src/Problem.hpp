#pragma once

#include "Maze.hpp"
#include "Matrix.hpp"
#include <string>
#include <vector>
#include "SearchAlgoritem.hpp"
namespace problem {
class Problem {
protected:
  const std::vector<std::string> m_inputFiles;
  const std::string m_typeOfProblem;

public:
  /**
   * @brief Construct a new Problem object
   *
   * @param inputFiles
   * @param typeOfProblem the specific problem (like add or convert)
   */
  Problem(const std::vector<std::string> &inputFiles,
          const std::string &typeOfProblem);
  /**
   * @brief solve the problem
   *
   * @return std::string the result in a string
   */
  virtual std::string solveProblem() const = 0;
  /**
   * @brief Destroy the Problem object
   *
   */
  virtual ~Problem();
};

class Matrix : public Problem {
private:
  std::string solveAdd() const;
  std::string solveMultiply() const;
  /**
   * @brief read the file and make a matrix out of it.
   *
   * @param inputFile the file
   * @return matrix::Matrix
   */
  static matrix::Matrix fileToMatrix(const std::string &inputFile);
  /**
   * @brief read the matrix and make a string out of it.
   *
   * @param matrix
   * @return std::string the matrix in a string
   */
  std::string matrixToString(const matrix::Matrix &matrix) const;

public:
  /**
   * @brief Construct a new Matrix object
   *
   * @param inputFiles
   * @param typeOfProblem the specific problem (like add or convert)
   */
  Matrix(const std::vector<std::string> &inputFiles,
         const std::string &typeOfProblem);
  /**
   * @brief solve the problem
   *
   * @return std::string the result in a string
   */
  std::string solveProblem() const;
};

class Image : public Problem {
private:
  /**
   * @brief solve the rotate problem
   *
   * @return std::string the result
   */
  std::string solveRotate() const;
  /**
   * @brief solve the convert problem
   *
   * @return std::string the result
   */
  std::string solveConvertToGray() const;

public:
  /**
   * @brief Construct a new Image object
   *
   * @param inputFiles
   * @param typeOfProblem the specific problem (like add or convert)
   */
  Image(const std::vector<std::string> &inputFiles,
        const std::string &typeOfProblem);
  /**
   * @brief solve the problem
   *
   * @return std::string the result in a string
   */
  std::string solveProblem() const;
};

class Hash : public Problem {
private:
  /**
   * @brief solve the crc problem
   *
   * @return std::string the result
   */
  std::string solveCrc() const;

public:
  /**
   * @brief Construct a new Hash object
   *
   * @param inputFiles
   * @param typeOfProblem the specific problem (like add or convert)
   */
  Hash(const std::vector<std::string> &inputFiles,
       const std::string &typeOfProblem);
  /**
   * @brief solve the problem
   *
   * @return std::string the result in a string
   */
  std::string solveProblem() const;
};

class Search : public Problem {
    private:
    maze::Maze* m_maze;
    std::string m_typeOfAlgoritem;
    public:
    Search(std::string const matrixInformation, const std::string typeOfAlgoritem, const std::string startPoint, const std::string endPoint);
    std::string solveProblem() const;
};

} // namespace problem