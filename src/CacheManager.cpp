#include "CacheManager.hpp"
#include "FileCopier.hpp"
#include "file_reading.hpp"
#include "Problem.cpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "Problem.hpp"

bool willEnd(std::string const &String, std::string const &ending) {
  if (String.length() >= ending.length()) {
    return (0 == String.compare(fullString.length() - ending.length(),
                                    ending.length(), ending));
  } 
   return false;
}

std::string findCachePath(const std::string &currenDirectory) {
  for (auto &p :
       std::filesystem::recursive_directory_iterator(currenDirectory)) {
    std::string path = p.path();
    if (willEnd(path, "src/bin/cache")) {
      return path;
    }
  }
  return "error";
}
manager::CacheManager::CacheManager(const std::vector<std::string> &inputFiles,
                                    const std::string &typeOfProblem,
                                    const std::string &typeOfCommand)
    : m_inputFiles(inputFiles), m_typeOfProblem(typeOfProblem),
      m_typeOfCommand(typeOfCommand) {
        m_cacheFolderPath = findCachePath(std::filesystem::current_path().c_str());
      m_filesNamesDoucumentPath = (findCachePath(std::filesystem::current_path().c_str()) + "/names.txt");
      }

std::string manager::CacheManager::convertToCacheFileName() const {
  std::string name;
  name += m_typeOfProblem;
  name += ",";
  name += m_typeOfCommand;
  name += ",";

  for (uint64_t i = 0; i < m_inputFiles.size(); i++) {
    std::vector <std::string> vec = {m_inputFiles[i]};
    auto prob =  std::make_unique<problem::Hash>(vec, "crc32");
    name += prob->solveProblem();
    name += ",";
  }
  return name;
}

std::vector<std::string>
manager::CacheManager::fromFileToVector(const std::string &filePath) const {
  std::ifstream file;
  const std::string content(file::readFileContent(filePath));
  char writer[1];
  int currentIdx = 0;
  writer[0] = content[currentIdx];
  std::vector<std::string> filesNames;
  int currentName = -1;
  while (writer[0] != '\0') {
    if (writer[0] == ' ') {
      currentName++;
      filesNames.push_back("");
    } else {
      filesNames[currentName] += writer[0];
    }
    currentIdx++;
    writer[0] = content[currentIdx];
  }
  return filesNames;
}

void manager::CacheManager::fromVectorToFile(
    const std::vector<std::string> &vector, const std::string &filePath) const {
  std::ofstream file;
  file.open(filePath, std::ios::out | std::ios::binary | std::ios::trunc);
  char writer[1];
  writer[0] = ' ';
  for (uint64_t i = 0; i < vector.size(); i++) {
    writer[0] = ' ';
    file.write(writer, 1);
    for (uint64_t j = 0; j < vector[i].size(); j++) {
      writer[0] = vector[i][j];
      file.write(writer, 1);
    }
  }
  file.close();
}

void manager::CacheManager::updateFilesNameDocumentCaseUse() const {
  std::vector<std::string> vectorOfNames(
      fromFileToVector(m_filesNamesDoucumentPath));
  for (uint64_t i = 0; i < vectorOfNames.size(); i++) {
    if (!vectorOfNames[i].compare(convertToCacheFileName())) {
      auto newVector = std::make_unique<std::vector<std::string>>(0);
      for (uint64_t j = 0; j < vectorOfNames.size(); j++) {
        if (i == j) {
          ;
        } else {
          newVector->push_back(vectorOfNames[j]);
        }
      }
      newVector->push_back(convertToCacheFileName());
      fromVectorToFile(*newVector, m_filesNamesDoucumentPath);
      return;
    }
  }
}

void manager::CacheManager::updateFilesNameDocumentCaseAdd() const {
  std::vector<std::string> vectorOfNames(
      fromFileToVector(m_filesNamesDoucumentPath));
  vectorOfNames.push_back(convertToCacheFileName());
  fromVectorToFile(vectorOfNames, m_filesNamesDoucumentPath);
}

bool manager::CacheManager::solutionAlreadyExistInCache() const {
  std::vector<std::string> vectorOfNames(
      fromFileToVector(m_filesNamesDoucumentPath));
  for (uint64_t i = 0; i < vectorOfNames.size(); i++) {
    if (vectorOfNames[i].compare(convertToCacheFileName())) {
      return true;
    }
  }
  return false;
}

void manager::CacheManager::createNewFileInCacheFolder(
    const std::string &content) const {
  std::string path(m_cacheFolderPath + "/" + convertToCacheFileName());
  std::ofstream file;
  file.open(path, std::ios::out | std::ios::binary | std::ios::trunc);
  file::writeFileContent(path, content);
  file.close();
}

void manager::CacheManager::useExistingSolution(
    const std::string &outputPath) const {
  auto copier = std::make_unique<copier::FileCopier>(
      m_cacheFolderPath + "/" + convertToCacheFileName(), outputPath);
  copier->copyInputToOutput();
  updateFilesNameDocumentCaseUse();
}

void manager::CacheManager::addSolution(const std::string &content) const {
  file::writeFileContent(m_cacheFolderPath + "/" + convertToCacheFileName(),
                         content);
  updateFilesNameDocumentCaseAdd();
}

void manager::CacheManager::clear() const {
  std::filesystem::remove_all(m_cacheFolderPath);
}