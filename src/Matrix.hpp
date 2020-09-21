#ifndef MATRIX_H
#define MATRIX_H
#pragma once

#include "Matrix.h"
#include "ErrorCode.h"

namespace matrix {
    /**
     * @brief the class matrix wrap the struct matrix.
     * implements operators and the rule of five.
     * 
     */
class Matrix
{
private:
    PMatrix m_matrix;
public:

    /**
     * @brief Construct a new Matrix object.
     * 
     * @param height the hight of the new matrix.
     * @param width the width of the new matrix.
     */
    
    Matrix(uint32_t height, uint32_t width);
    /**
     * @brief 
     * 
     * @param other 
     * @return Matrix 
     */

    Matrix& operator=(const Matrix& other);
    /** 
    * @brief Construct a new Matrix object
    * 
    * @param other 
    */
   
   /**
    * @brief Construct a new Matrix object
    * 
    * @param other 
    */
    Matrix(const Matrix& other);

    /**
    * @brief Construct a new Matrix object
    * 
    * @param other 
    */
    Matrix(Matrix&& other) noexcept;

    /**
     * @brief 
    * 
    * @param other 
    * @return Matrix 
    */
    Matrix& operator=(Matrix&& other) noexcept;
   
    /**
     * @brief Get the Hight of the matrix.
     * 
     * @return uint32_t 
     */
    
    uint32_t getHight() const;
        /**
     * @brief Get the with of the matrix.
     * 
     * @return uint32_t 
     */
    
    uint32_t getWidth() const;
    /**
     * @brief Set the value of a certain cell in the matrix.
     * 
     * @param rowIndex the num of the row.
     * @param colIndex the num of the column.
     * @param value the new value of the cell.
     */
    
    void setValue(uint32_t rowIndex, uint32_t colIndex, double value);
    /**
     * @brief Get the Value of a cell in the matrix.
     * 
     * @param rowIndex the num of the row.
     * @param colIndex the num of the column.
     * @return double 
     */
    double getValue(uint32_t rowIndex, uint32_t colIndex) const;
    /**
     * @brief add the matrixes and the result is in this matrix.
     * 
     * @param other the other matrix we add. 
     */
    Matrix add(const Matrix& other) const;
    /**
     * @brief multiply the matrix with a scalar.
     * 
     * @param scalar the number we multiply with.
     */
    Matrix multiplyWithScalar(double scalar) const;
    /**
     * @brief get another matrix and multiply them.
     * this X rhs
     * 
     * @param rhs the matrix we multiply with.
     */
    Matrix multiplyFromRight(const Matrix& rhs) const;
    /**
     * @brief Destroy the Matrix object
     * 
     */
    /**
     * @brief get another matrix and multiply them.
     * this X rhs
     * 
     * @param rhs the matrix we multiply with.
     */
    Matrix multiplyFromLeft(const Matrix& lhs) const;
    /**
     * @brief Destroy the Matrix object.
     * 
     */
    ~Matrix();
    Matrix& rotateMatrix() const;
};
}
#endif

