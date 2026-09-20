#pragma once
#include "endergfx/Texture.hpp"
#include <bgfx/bgfx.h>

namespace endergfx {

enum class BlendMode : uint64_t {
  Opaque = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z,
  Transparent = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z |
                BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA,
                                      BGFX_STATE_BLEND_INV_SRC_ALPHA),
  Additive =
      BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_Z |
      BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_ONE),
  Multiply =
      BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_Z |
      BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ZERO, BGFX_STATE_BLEND_SRC_COLOR),
  Screen = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_Z |
           BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE,
                                 BGFX_STATE_BLEND_INV_SRC_COLOR),
};

struct MaterialProperties {
  Texture baseTexture;
  BlendMode blendMode = BlendMode::Opaque;
  float opacity = 1.0f;
};

class Material {
public:
  explicit Material(const MaterialProperties &props);
  Material();

  const Texture &texture() const { return this->m_baseTexture; }
  BlendMode blendMode() const { return this->m_blendMode; }
  float opacity() const { return this->m_opacity; }
  void setOpacity(float value) { this->m_opacity = value; }

private:
  Texture m_baseTexture;
  BlendMode m_blendMode;
  float m_opacity;
};

} // namespace endergfx
