#pragma once
#include "endergfx/Mesh.hpp"
#include <string>
#include <vector>

namespace endergfx {

class ModelLoader {
public:
  static std::vector<Mesh> loadOBJ(const std::string &path);
};

} // namespace endergfx
