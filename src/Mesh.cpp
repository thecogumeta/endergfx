#include "endergfx/Mesh.hpp"
#include "endergfx/Log.hpp"

namespace endergfx {

Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<uint16_t> &indices) {
  const bgfx::Memory *vmem = bgfx::copy(
      vertices.data(), static_cast<uint32_t>(vertices.size() * sizeof(Vertex)));
  this->m_vbh = bgfx::createVertexBuffer(vmem, Vertex::layout());

  const bgfx::Memory *imem = bgfx::copy(
      indices.data(), static_cast<uint32_t>(indices.size() * sizeof(uint16_t)));
  this->m_ibh = bgfx::createIndexBuffer(imem);

  if (!bgfx::isValid(this->m_vbh) || !bgfx::isValid(this->m_ibh)) {
    log(LogLevel::Error, "Failed to create mesh buffers");
  }
}

Mesh::~Mesh() {
  if (bgfx::isValid(this->m_vbh)) {
    bgfx::destroy(this->m_vbh);
  }
  if (bgfx::isValid(this->m_ibh)) {
    bgfx::destroy(this->m_ibh);
  }
}

Mesh::Mesh(Mesh &&other) noexcept : m_vbh(other.m_vbh), m_ibh(other.m_ibh) {
  other.m_vbh = BGFX_INVALID_HANDLE;
  other.m_ibh = BGFX_INVALID_HANDLE;
}

Mesh &Mesh::operator=(Mesh &&other) noexcept {
  if (this != &other) {
    if (bgfx::isValid(this->m_vbh))
      bgfx::destroy(this->m_vbh);
    if (bgfx::isValid(this->m_ibh))
      bgfx::destroy(this->m_ibh);
    this->m_vbh = other.m_vbh;
    this->m_ibh = other.m_ibh;
    other.m_vbh = BGFX_INVALID_HANDLE;
    other.m_ibh = BGFX_INVALID_HANDLE;
  }
  return *this;
}

void Mesh::bind() const {
  bgfx::setVertexBuffer(0, this->m_vbh);
  bgfx::setIndexBuffer(this->m_ibh);
}

} // namespace endergfx
