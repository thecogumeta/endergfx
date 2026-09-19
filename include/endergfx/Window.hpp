#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <string>

namespace endergfx {

struct WindowConfig {
  std::string title = "endergfx";
  int width = 1280;
  int height = 720;
  bool resizable = true;
  bool fullscreen = false;
  bool relativeMouseMode = false;
  SDL_WindowFlags extraFlags = 0;
};

using ResizeCallback = std::function<void(int width, int height)>;

class Window {
public:
  explicit Window(const WindowConfig &config = {});
  ~Window();

  void setRelativeMouseMode(bool enabled);
  void setResizeCallback(ResizeCallback callback);

  void handleEvent(SDL_Event &event);
  bool isRunning() const { return this->m_running; }

  SDL_Window *native() const { return this->m_window; }

private:
  SDL_Window *m_window = nullptr;
  bool m_running;
  ResizeCallback m_resizeCallback;
};

} // namespace endergfx
