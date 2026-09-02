#pragma once
#include <bgfx/bgfx.h>

namespace endergfx {

struct Vertex {
  float x, y, z;
  uint32_t abgr;

  static bgfx::VertexLayout layout() {
    static bgfx::VertexLayout layout;
    static bool initialized = false;
    if (!initialized) {
      layout.begin()
          .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
          .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
          .end();
      initialized = true;
    }
    return layout;
  }
};

} // namespace endergfx
