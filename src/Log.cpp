#include "endergfx/Log.hpp"
#include <cstdio>

namespace endergfx {

namespace {

LogCallback g_logCallback = nullptr;

const char *levelToString(LogLevel level) {
  switch (level) {
  case LogLevel::Debug:
    return "DEBUG";
  case LogLevel::Info:
    return "INFO";
  case LogLevel::Warning:
    return "WARN";
  case LogLevel::Error:
    return "ERROR";
  }
  return "UNKNOWN";
}

void defaultLogCallback(LogLevel level, const std::string &message) {
  std::FILE *stream = (level == LogLevel::Error || level == LogLevel::Warning)
                          ? stderr
                          : stdout;
  std::fprintf(stream, "[EnderGFX] [%s] %s\n", levelToString(level),
               message.c_str());
}

} // namespace

void setLogCallback(LogCallback callback) {
  g_logCallback = std::move(callback);
}

void log(LogLevel level, const std::string &message) {
  if (g_logCallback) {
    g_logCallback(level, message);
  } else {
    defaultLogCallback(level, message);
  }
}

} // namespace endergfx
