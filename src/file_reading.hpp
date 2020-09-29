#include <string>

namespace file{

std::string readFileContent(const std::string& filePath);

void writeFileContent(const std::string& filePath, const std::string& content);

}