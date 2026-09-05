#pragma once

namespace endergfx {

class Light {
public:
  void setDirection(float x, float y, float z);
  void setColor(float r, float g, float b);
  void setAmbient(float intensity);

  const float *direction() const { return this->m_direction; }
  const float *color() const { return this->m_color; }
  float ambient() const { return this->m_ambient; }

private:
  float m_direction[3] = {0.3f, 0.7f, -0.5f};
  float m_color[3] = {1.0f, 1.0f, 1.0f};
  float m_ambient = 0.25f;
};

} // namespace endergfx
