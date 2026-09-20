#include "endergfx/Material.hpp"

namespace endergfx {

Material::Material()
    : m_baseTexture(Texture::createSolidColor(255, 255, 255, 255)),
      m_blendMode(BlendMode::Opaque), m_opacity(1.0f) {}

Material::Material(const MaterialProperties &props)
    : m_baseTexture(std::move(const_cast<Texture &>(props.baseTexture))),
      m_blendMode(props.blendMode), m_opacity(props.opacity) {}

} // namespace endergfx
