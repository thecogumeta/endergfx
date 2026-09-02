#include "endergfx/Camera.hpp"
#include <bgfx/bgfx.h>
#include <bx/math.h>

namespace endergfx {

Camera::Camera() {
  this->updateView();
  this->setPerspective(60.0f, 16.0f / 9.0f, 0.1f, 100.0f);
}

void Camera::setPosition(float x, float y, float z) {
  this->m_position[0] = x;
  this->m_position[1] = y;
  this->m_position[2] = z;
  this->updateView();
}

void Camera::lookAt(float x, float y, float z) {
  this->m_target[0] = x;
  this->m_target[1] = y;
  this->m_target[2] = z;
  this->updateView();
}

void Camera::updateView() {
  const bx::Vec3 eye = {this->m_position[0], this->m_position[1],
                        this->m_position[2]};
  const bx::Vec3 at = {this->m_target[0], this->m_target[1], this->m_target[2]};
  const bx::Vec3 up = {0.0f, 1.0f, 0.0f};
  bx::mtxLookAt(this->m_view, eye, at, up);
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
