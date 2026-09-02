#pragma once
#include "endergfx/Camera.hpp"
#include "endergfx/Window.hpp"
#include <bgfx/bgfx.h>

namespace endergfx {

class Renderer {
public:
  Renderer(Window &window, int width, int height);
  ~Renderer();

  void beginFrame();
  void endFrame();

  void setCamera(bgfx::ViewId view, const Camera &camera);

  bool isValid() const { return this->m_valid; }

private:
  int m_width;
  int m_height;
  bool m_valid = false;
};

} // namespace endergfx
