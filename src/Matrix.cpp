#include "Matrix.hpp"
#include "ErrorCodeException.hpp"
#include<memory>
#include <vector>

//a regular constructor to the class
matrix :: Matrix :: Matrix(uint32_t height, uint32_t width){
    //use the methods from the c library to allocate the struct field.
    ErrorCode errorCode = matrix_create(&m_matrix, height, width);
    //throw an exception if there is an error
    if(!error_isSuccess(errorCode)) {
        Error::ErrorCodeException errorException(errorCode);
        throw errorException;
    }
}

//a copy constructor to the class.
matrix :: Matrix :: Matrix(const Matrix& other) {
    //use the methods from the c library to allocate the struct field.
    ErrorCode errorCodeCreate = matrix_create(&m_matrix, other.getHight(), other.getWidth());
     //throw an exception if there is an error
    if(!error_isSuccess(errorCodeCreate)) {
        Error::ErrorCodeException errorException(errorCodeCreate);
        throw errorException;
    }
    //use the methods from the c library to copy the method from the other's struct to this.
    ErrorCode errorCodeCopy = matrix_copy(&m_matrix, other.m_matrix);
     //throw an exception if there is an error
    if(!error_isSuccess(errorCodeCopy)) {
        Error::ErrorCodeException errorException(errorCodeCopy);
        throw errorException;
    }
}

matrix::Matrix&  matrix :: Matrix :: operator=(const Matrix& other) {
    if(this == &other) {
        return *this;
    }
    matrix_destroy(m_matrix);
    *this = Matrix(other);
    return *this;
}

matrix :: Matrix :: Matrix(Matrix&& other) noexcept {
    matrix_create(&m_matrix, other.getHight(), other.getWidth());
    matrix_copy(&m_matrix, other.m_matrix);
    matrix_destroy(other.m_matrix);
    other.m_matrix = nullptr;
}

matrix::Matrix&  matrix :: Matrix :: operator=(Matrix&& other) noexcept {
    if(this == &other) {
        return *this;
    }
    matrix_destroy(m_matrix);
    matrix_copy(&m_matrix, other.m_matrix); 
    matrix_destroy(other.m_matrix);
    return *this;
}


uint32_t matrix :: Matrix :: getHight() const {
    uint32_t result;
    ErrorCode errorCode = matrix_getHeight(m_matrix, &result);
    if(!error_isSuccess(errorCode)) {
        Error::ErrorCodeException errorException(errorCode);
        throw errorException;
    }
    return result;
}

uint32_t matrix :: Matrix :: getWidth() const {
    uint32_t result;
    ErrorCode errorCode = matrix_getWidth(m_matrix,&result);
    if(!error_isSuccess(errorCode)) {
        Error::ErrorCodeException errorException(errorCode);
        throw errorException;
    }
    return result;
}

void matrix :: Matrix :: setValue(uint32_t rowIndex, uint32_t colIndex, double value){
    ErrorCode errorCode = matrix_setValue(m_matrix, rowIndex, colIndex, value);
    if(!error_isSuccess(errorCode)) {
        Error::ErrorCodeException errorException(errorCode);
        throw errorException;
    }
}

double matrix :: Matrix :: getValue(uint32_t rowIndex, uint32_t colIndex) const {
    double value;
    ErrorCode errorCode = matrix_getValue(m_matrix, rowIndex, colIndex, &value);
    if(!error_isSuccess(errorCode)) {
        Error::ErrorCodeException errorException(errorCode);
        throw errorException;
    }
    return value;
}

matrix::Matrix  matrix :: Matrix :: multiplyWithScalar(double scalar) const{
    const auto result = std::make_unique<Matrix>(this->getHight(), this->getWidth());
    ErrorCode errorCodeCopy = matrix_copy(&result->m_matrix,this->m_matrix);
     if(!error_isSuccess(errorCodeCopy)) {
        Error::ErrorCodeException errorException(errorCodeCopy);
        throw errorException;
    }
    ErrorCode errorCode = matrix_multiplyWithScalar(result->m_matrix, scalar);
    if(!error_isSuccess(errorCode)) {
        Error::ErrorCodeException errorException(errorCode);
        throw errorException;
    }
    return *result;
}

matrix::Matrix  matrix :: Matrix :: add(const Matrix& other) const{
    const auto result = std::make_unique<Matrix>(this->getHight(), this->getWidth());
    ErrorCode errorCodeCopy = matrix_copy(&result->m_matrix,this->m_matrix);
     if(!error_isSuccess(errorCodeCopy)) {
        Error::ErrorCodeException errorException(errorCodeCopy);
        throw errorException;
    }
    ErrorCode errorCodeAdd = matrix_add(&result->m_matrix, this->m_matrix, other.m_matrix);
    if(!error_isSuccess(errorCodeAdd)) {
        Error::ErrorCodeException errorException(errorCodeAdd);
        throw errorException;
    }
    return *result;
}
    
matrix::Matrix matrix :: Matrix :: multiplyFromRight(const Matrix& rhs)const {
    const auto result = std::make_unique<Matrix>(this->getHight(), this->getWidth());
    ErrorCode errorCodeCopy = matrix_copy(&result->m_matrix,this->m_matrix);
    if(!error_isSuccess(errorCodeCopy)) {
        Error::ErrorCodeException errorException(errorCodeCopy);
        throw errorException;
    }
    ErrorCode errorCodeMul = matrix_multiplyMatrices(&result->m_matrix, rhs.m_matrix, this->m_matrix);
    if(!error_isSuccess(errorCodeMul)) {
        Error::ErrorCodeException errorException(errorCodeMul);
        throw errorException;
    }
    return *result;
}

matrix::Matrix matrix :: Matrix :: multiplyFromLeft(const Matrix& lhs)const {
    const auto result = std::make_unique<Matrix>(this->getHight(), this->getWidth());
    ErrorCode errorCodeCopy = matrix_copy(&result->m_matrix,this->m_matrix);
    if(!error_isSuccess(errorCodeCopy)) {
        Error::ErrorCodeException errorException(errorCodeCopy);
        throw errorException;
    }
    ErrorCode errorCodeMul = matrix_multiplyMatrices(&result->m_matrix, lhs.m_matrix, this->m_matrix);
    if(!error_isSuccess(errorCodeMul)) {
        Error::ErrorCodeException errorException(errorCodeMul);
        throw errorException;
    }
    return *result;
}
matrix::Matrix& matrix::Matrix::rotateMatrix() const{
    const auto result = std::make_unique<Matrix>(this->getHight(), this->getWidth());
    for(uint32_t i = 0 ; i < this->getWidth(); ++i){
        for(uint32_t j = 0; j < this->getHight(); ++j){
            result->setValue(i, result->getWidth()-1 - j, this->getValue(j,i));
        }
    }
    return *result;
}

matrix::Matrix::~Matrix() {
    matrix_destroy(m_matrix);
}
