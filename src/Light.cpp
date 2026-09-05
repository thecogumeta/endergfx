#include "endergfx/Light.hpp"

namespace endergfx {

void Light::setDirection(float x, float y, float z) {
  this->m_direction[0] = x;
  this->m_direction[1] = y;
  this->m_direction[2] = z;
}

void Light::setColor(float r, float g, float b) {
  this->m_color[0] = r;
  this->m_color[1] = g;
  this->m_color[2] = b;
}

void Light::setAmbient(float intensity) { this->m_ambient = intensity; }

} // namespace endergfx
