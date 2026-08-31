#include "endergfx/Window.hpp"
#include "endergfx/Log.hpp"

namespace endergfx {

Window::Window(const WindowConfig &config) {
  SDL_WindowFlags flags = config.extraFlags;

  if (config.resizable) {
    flags |= SDL_WINDOW_RESIZABLE;
  }
  if (config.fullscreen) {
    flags |= SDL_WINDOW_FULLSCREEN;
  }

  this->m_window = SDL_CreateWindow(config.title.c_str(), config.width,
                                    config.height, flags);

  if (!this->m_window) {
    log(LogLevel::Error,
        std::string("Failed to create window: ") + SDL_GetError());
    this->m_running = false;
    return;
  }

  this->m_running = true;

  if (config.relativeMouseMode) {
    this->setRelativeMouseMode(true);
  }
}

Window::~Window() {
  if (this->m_window) {
    SDL_DestroyWindow(this->m_window);
  }
}

void Window::setRelativeMouseMode(bool enabled) {
  SDL_SetWindowRelativeMouseMode(this->m_window, enabled);
}

void Window::handleEvent(SDL_Event &event) {
  switch (event.type) {
  case SDL_EVENT_QUIT:
    this->m_running = false;
    break;

  case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
    if (SDL_GetWindowID(this->m_window) == event.window.windowID) {
      this->m_running = false;
    }
    break;

  default:
    break;
  }
}

} // namespace endergfx
