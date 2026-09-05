#include "endergfx/Material.hpp"

namespace endergfx {

Material::Material()
    : m_texture(Texture::createSolidColor(255, 255, 255, 255)) {}

Material::Material(Texture texture) : m_texture(std::move(texture)) {}

} // namespace endergfx
