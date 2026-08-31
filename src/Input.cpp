#include "endergfx/Input.hpp"

namespace endergfx {

void Input::handleEvent(const SDL_Event &event) {
  switch (event.type) {
  case SDL_EVENT_KEY_DOWN:
    this->m_keyState[event.key.scancode] = true;
    break;

  case SDL_EVENT_KEY_UP:
    this->m_keyState[event.key.scancode] = false;
    break;

  case SDL_EVENT_MOUSE_MOTION:
    this->m_mouseDeltaX += event.motion.xrel;
    this->m_mouseDeltaY += event.motion.yrel;
    break;

  default:
    break;
  }
}

void Input::resetFrameState() {
  this->m_mouseDeltaX = 0.0f;
  this->m_mouseDeltaY = 0.0f;
}

bool Input::isKeyDown(SDL_Scancode key) const { return this->m_keyState[key]; }

} // namespace endergfx
