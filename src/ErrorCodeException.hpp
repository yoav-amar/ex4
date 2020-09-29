#ifndef ERROR_HPP
#define ERROR_HPP
#include "ErrorCode.h"
#include <iostream>
#include <exception>
namespace Error{   
     /**
     * @brief the errorCodeException class wrrap the Errorcode and its
     * perpose is to be thrown as exception.
     * 
     */

    class ErrorCodeException : public std :: exception {
    private :
    ErrorCode m_error;
    public :
    /**
     * @brief Construct a new Error Code Exception object
     * 
     * @param error the error code of the error code exception.
     */
    ErrorCodeException(ErrorCode error);

    /**
    * @brief Get the Error Code object
    * 
    * @return ErrorCode 
    */
    ErrorCode getErrorCode()const;
   /**
    * @brief print the message of the errorcode.
    * 
    */
    void printErrorMessage() const;
};
}
#endif