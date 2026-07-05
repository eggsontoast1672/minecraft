#include <minecraft/filesystem.hpp>

#include <cstring>
#include <fstream>
#include <sstream>

std::string load_from_path(const char *path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    std::ostringstream message;
    message << path << ": " << std::strerror(errno);
    throw std::runtime_error(message.str());
  }

  std::ostringstream contents;
  contents << file.rdbuf();
  return contents.str();
}
