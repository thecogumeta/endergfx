#include "endergfx/Camera.hpp"
#include <bgfx/bgfx.h>
#include <bx/math.h>

namespace endergfx {

Camera::Camera() {
  this->updateView();
  this->setPerspective(60.0f, 16.0f / 9.0f, 0.1f, 100.0f);
}

void Camera::setPosition(float x, float y, float z) {
  this->m_position.x = x;
  this->m_position.y = y;
  this->m_position.z = z;
  this->updateView();
}

void Camera::lookAt(float x, float y, float z) {
  this->m_target.x = x;
  this->m_target.y = y;
  this->m_target.z = z;
  this->updateView();
}

void Camera::updateView() {
  const bx::Vec3 up = {0.0f, 1.0f, 0.0f};
  bx::mtxLookAt(this->m_view, this->m_position, this->m_target, up);
}

void Camera::setPerspective(float fovDegrees, float aspect, float near,
                            float far) {
  bx::mtxProj(this->m_proj, fovDegrees, aspect, near, far,
              bgfx::getCaps()->homogeneousDepth);
}

void Camera::setOrtho(float left, float right, float bottom, float top,
                      float near, float far) {
  bx::mtxOrtho(this->m_proj, left, right, bottom, top, near, far, 0.0f,
               bgfx::getCaps()->homogeneousDepth);
}

} // namespace endergfx
