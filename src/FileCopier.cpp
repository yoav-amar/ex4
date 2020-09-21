#include "FileCopier.hpp"
#include "file_reading.hpp"
#include "string"

copier::FileCopier::FileCopier(const std::string &inputFilePath,
                               const std::string &outputFilePath)
    : m_inputFilePath(inputFilePath), m_outputFilePath(outputFilePath) {}

void copier::FileCopier::copyInputToOutput() {
  file::writeFileContent(m_outputFilePath, file::readFileContent(m_inputFilePath));
}