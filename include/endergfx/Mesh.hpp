#pragma once
#include "endergfx/Vertex.hpp"
#include <bgfx/bgfx.h>
#include <vector>

namespace endergfx {

class Mesh {
public:
  Mesh(const std::vector<Vertex> &vertices,
       const std::vector<uint16_t> &indices);
  ~Mesh();

  Mesh(const Mesh &) = delete;
  Mesh &operator=(const Mesh &) = delete;
  Mesh(Mesh &&other) noexcept;
  Mesh &operator=(Mesh &&other) noexcept;

  void bind() const;

private:
  bgfx::VertexBufferHandle m_vbh = BGFX_INVALID_HANDLE;
  bgfx::IndexBufferHandle m_ibh = BGFX_INVALID_HANDLE;
};

} // namespace endergfx
