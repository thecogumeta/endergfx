#pragma once
#include <SDL3/SDL.h>

namespace endergfx {

class Input {
public:
  void handleEvent(const SDL_Event &event);
  void resetFrameState();

  float mouseDeltaX() const { return this->m_mouseDeltaX; }
  float mouseDeltaY() const { return this->m_mouseDeltaY; }
  bool isKeyDown(SDL_Scancode key) const;

private:
  float m_mouseDeltaX = 0.0f;
  float m_mouseDeltaY = 0.0f;
  bool m_keyState[SDL_SCANCODE_COUNT] = {};
};

} // namespace endergfx
