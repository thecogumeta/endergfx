#pragma once
#include <SDL3/SDL.h>
#include <string>

namespace endergfx::PathUtils {

inline std::string getExecutableDir() {
  const char *path = SDL_GetBasePath();
  return path ? std::string(path) : "./";
}

} // namespace endergfx::PathUtils
