#include "CacheException.hpp"
#include "ErrorCache.hpp"
#include "file_reading.hpp"
#include <string>
namespace copier {
class FileCopier {
private:
  std::string m_inputFilePath;
  std::string m_outputFilePath;

public:
  /**
   * @brief Construct a new File Copier object.
   *
   * @param inputFilePath is a path to an existing to file that we want to copy
   * its content to another file.
   * @param outputFilePath is a path to an existing file that we want to update
   * with an wxisting content.
   */
  FileCopier(const std::string &inputFilePath,
             const std::string &outputFilePath);

  /**
   * @brief copy the content from the input file to the output.
   *
   */
  void copyInputToOutput();
};
} // namespace copier