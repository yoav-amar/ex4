#include "CacheException.hpp"
#include "ErrorCache.hpp"
#include "iostream"

cacheExcption::CacheExcpetion::CacheExcpetion(
    const error::ErrorCacheType &errorType)
    : m_error(errorType){}

cacheExcption::CacheExcpetion::CacheExcpetion(const error::ErrorCache &error)
    : m_error(error){}

error::ErrorCache cacheExcption::CacheExcpetion::getError() const {
  return m_error;
}

void cacheExcption::CacheExcpetion::printErrorMessage() const {
  std::cout << m_error.getErrorMessage() << std::endl;
}