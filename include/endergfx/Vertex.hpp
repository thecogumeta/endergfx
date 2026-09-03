#pragma once
#include <bgfx/bgfx.h>

namespace endergfx {

struct Vertex {
  float x = 0.0f, y = 0.0f, z = 0.0f;    // pos
  float nx = 0.0f, ny = 0.0f, nz = 0.0f; // normal
  float u = 0.0f, v = 0.0f;              // texcoord
  uint32_t abgr = 0xffffffff;            // color

  static bgfx::VertexLayout layout() {
    static bgfx::VertexLayout layout;
    static bool initialized = false;
    if (!initialized) {
      layout.begin()
          .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
          .add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
          .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
          .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
          .end();
      initialized = true;
    }
    return layout;
  }
};

} // namespace endergfx
