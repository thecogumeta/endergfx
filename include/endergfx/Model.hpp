#pragma once
#include "endergfx/Mesh.hpp"
#include <bgfx/bgfx.h>

namespace endergfx {

class Model {
public:
  explicit Model(const Mesh &mesh);
  Model(const Mesh &mesh, bgfx::ProgramHandle program);

  ~Model();

  Model(const Model &) = delete;
  Model &operator=(const Model &) = delete;

  void setPosition(float x, float y, float z);
  void setRotation(float x, float y, float z);
  void setScale(float x, float y, float z);

  void draw(bgfx::ViewId view) const;

private:
  const Mesh &m_mesh;
  bgfx::ProgramHandle m_program;
  bool m_ownsProgram;

  struct {
    float x, y, z;
  } m_position{0, 0, 0};
  struct {
    float x, y, z;
  } m_rotation{0, 0, 0};
  struct {
    float x, y, z;
  } m_scale{1, 1, 1};
};

} // namespace endergfx
