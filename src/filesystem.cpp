#include <minecraft/filesystem.hpp>

#include <fstream>
#include <sstream>

std::string load_from_path(const char *path) {
  std::ifstream file(path);
  std::ostringstream contents;
  contents << file.rdbuf();
  return contents.str();
}
