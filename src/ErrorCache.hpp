#pragma once
#include <string>
// name space error
namespace error {
// define an enummer so we would be able to seperate the types of error in an
// obious way.
enum ErrorCacheType {
  error_success = 0,
  error_input_file1_doesnt_exist,
  error_input_file2_doesnt_exist,
  error_not_supported_this_kind_of_problem,
  error_Wrong_number_of_input_files,
  error_cant_read_file,
  error_cant_write_to_file,
  error_cant_solve_the_problem,
  error_memory_allocate_failed,
  error_wrong_number_of_arguments,
  error_Wrong_dimensions
};
// define a class error to wrap the the enummer so we would be able to define
// methods on it.
class ErrorCache {
private:
  // a filed that saces the type of error.
  ErrorCacheType m_errorType;

public:
  /**
   * @brief Construct a new Error Cache object.
   *
   * @param error enummer type that describe a kind of error.
   */
  ErrorCache(const ErrorCacheType error);

  /**
   * @brief to know if the type of error is success or not.
   *
   * @return true if the type of error is true.
   * @return false if the type of error is false.
   */
  bool errorIsSuccess() const;

  /**
   * @brief Get a string the describe the error.
   *
   * @return std::string -the error message.
   */
  std::string getErrorMessage() const;

  /**
   * @brief Get the Error Cache Type object.
   *
   * @return ErrorCacheType .
   */
  ErrorCacheType getErrorCacheType() const;
};
} // namespace error
