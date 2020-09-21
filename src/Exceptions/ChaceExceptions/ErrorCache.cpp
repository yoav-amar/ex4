#include "ErrorCache.hpp"
#include <string>

error::ErrorCache::ErrorCache(const ErrorCacheType errorType) {
  m_errorType = errorType;
}

bool error::ErrorCache::errorIsSuccess() const {
  // because errorSuccess = 0 always.
  return !m_errorType;
}

std::string error::ErrorCache::getErrorMessage() const {
  switch (m_errorType) {
  // if the error is "errorSuccess".
  case error_success:
    return "the error is success";
    break;
  // if the error is "error_input_file1_doesnt_exist".
  case error_input_file1_doesnt_exist:
    return "the first input file (the only one if you enter only one) is not "
           "exist.\ncheck it out, maybe it is a typo.";
    break;
    // if the error is "error_input_file1_doesnt_exist".
  case error_input_file2_doesnt_exist:
    return "the second input file (the only one if you enter only one) is not "
           "exist.\ncheck it out, maybe it is a typo.";
    break;
    // if the error is "error_not_supported_this_kind_of_problem".
  case error_not_supported_this_kind_of_problem:
    return "the program does not support this kind of problem.\ncheck it out, "
           "maybe it is a typo.";
    break;
  case error_Wrong_number_of_input_files:
    return "thre was a worng number of input files.";
    break;
  case error_cant_read_file:
    return "has problem in reading the file.";
    break;
  case error_cant_write_to_file:
    return "has a problem writing the string to the file";
    break;
  case error_cant_solve_the_problem:
    return "while solving the problem accured an error.";
    case error_wrong_number_of_arguments:
    return "the program does not support this number of arguments "
           "maybe it is a typo.";
    break;
  // does'nt suppose to happen...
  default:
    return NULL;
    break;
  }
}

error::ErrorCacheType error::ErrorCache::getErrorCacheType() const {
  return m_errorType;
}
