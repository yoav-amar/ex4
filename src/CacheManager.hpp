#pragma once
#include <string>
#include <vector>

namespace manager {
class CacheManager {
private:
  const std::string m_filesNamesDoucumentPath;
  const std::string m_cacheFolderPath;
  std::vector<std::string> m_inputFiles;
  std::string m_typeOfProblem;
  std::string m_typeOfCommand;
  std::string convertToCacheFileName() const;
  void createNewFileInCacheFolder(const std::string &content) const;
  void updateFilesNameDocumentCaseAdd() const;
  void updateFilesNameDocumentCaseUse() const;
  void fromVectorToFile(const std::vector<std::string> &vector,
                        const std::string &filePath) const;
  std::vector<std::string> fromFileToVector(const std::string &filePath) const;

public:
  CacheManager(const std::vector<std::string> &inputFiles,
               const std::string &typeOfProblem,
               const std::string &typeOfCommand);
  bool solutionAlreadyExistInCache() const;
  void useExistingSolution(const std::string &outputPath) const;
  void addSolution(const std::string &content) const;
  void clear() const;
};
} // namespace manager