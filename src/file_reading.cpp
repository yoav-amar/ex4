#include <fstream>
#include <iterator>
#include <string>
#include "file_reading.hpp"
#include "CacheException.hpp"

/**
 * @brief Read the content of a file at path filePath.
 *
 * @param filePath The relative or absolute path to the file.
 * @return std::string File's content
 */
std::string file::readFileContent(const std::string& filePath) {
  // Opens input-only file (ifstream) in binary mode.
  std::ifstream in(filePath, std::ios::binary);

  // The file is in a bad state. The error can be retrieved
  //	using the global `errno` in linux (#include <cerrno>).
  if (!in) {
    throw cacheExcption::CacheExcpetion(error::error_cant_read_file);
  }

  // Read the file to a vector. This is not the most effecient
  //	method to read a file.
  auto content = std::string{std::istreambuf_iterator<char>{in},
                             std::istreambuf_iterator<char>{}};


  return content;
}

/**
 * @brief Writes content to a file. If the file exists, removes
 *  previos content. Otherwise, creates a new file.
 *
 * @param filePath The relative or absolute path to the file.
 * @param content Content to write.
 */
void file::writeFileContent(const std::string& filePath, const std::string& content) {
  // Opens output-only file (ofstream) in binary mode, and truncates all
  //    existing content from the file.
  std::ofstream out(filePath, std::ios::binary | std::ios::trunc);

  // The file is in a bad state.
  if (!out) {
    throw cacheExcption::CacheExcpetion(error::error_cant_write_to_file);

  }

  out.write(content.data(), static_cast<std::streamsize>(content.length()));
  if (!out) {
    throw cacheExcption::CacheExcpetion(error::error_cant_write_to_file);
  }
}
