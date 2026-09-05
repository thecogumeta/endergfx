#pragma once
#include "endergfx/Texture.hpp"

namespace endergfx {

class Material {
public:
  Material();
  explicit Material(Texture texture);

  const Texture &texture() const { return this->m_texture; }

private:
  Texture m_texture;
};

} // namespace endergfx
