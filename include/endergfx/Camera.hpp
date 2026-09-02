#pragma once

namespace endergfx {

class Camera {
public:
  Camera();

  void setPosition(float x, float y, float z);
  void lookAt(float x, float y, float z);

  void setPerspective(float fovDegrees, float aspect, float near, float far);
  void setOrtho(float left, float right, float bottom, float top, float near,
                float far);

  const float *viewMatrix() const { return this->m_view; }
  const float *projMatrix() const { return this->m_proj; }

private:
  void updateView();

  float m_position[3] = {0.0f, 0.0f, -5.0f};
  float m_target[3] = {0.0f, 0.0f, 0.0f};

  float m_view[16];
  float m_proj[16];
};

} // namespace endergfx
