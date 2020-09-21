#include "ErrorCodeException.hpp"
#include "ErrorCode.h"

   Error :: ErrorCodeException :: ErrorCodeException(ErrorCode error) : m_error(error) {}

    ErrorCode Error :: ErrorCodeException :: getErrorCode() const{
        ErrorCode error = Error :: ErrorCodeException :: m_error;
        return error;
    }
   
    void Error :: ErrorCodeException :: printErrorMessage() const {
        std::string message = error_getErrorMessage(Error :: ErrorCodeException :: m_error);
        std::cout << message << std::endl;
    }
