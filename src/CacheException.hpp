#pragma once

#include "ErrorCache.hpp"
#include <exception>
#include <iostream>
namespace cacheExcption {
class CacheExcpetion : public std::exception {
private:
  // a ErrorCache field, we will use it to implement our methods.
  error::ErrorCache m_error;

public:
  /**
   * @brief Construct a new Cache Excpetion object (from error type).
   *
   */
  CacheExcpetion(const error::ErrorCacheType &errorType);

  /**
   * @brief Construct a new Cache Excpetion object(from errorCache).
   *
   */
  CacheExcpetion(const error::ErrorCache &error);

  /**
   * @brief print a message that will describe the error that happned.
   *
   */
  void printErrorMessage() const;

  /**
   * @brief Get the Error Type object.
   *
   * @return error::ErrorCacheType - the error type of the error.
   */
  error::ErrorCache getError() const;
};
} // namespace cacheExcption