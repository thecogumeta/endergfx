#pragma once
#include <bgfx/bgfx.h>
#include <string>

namespace endergfx {

class Texture {
public:
  explicit Texture(const std::string &path);

  static Texture createSolidColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  ~Texture();

  Texture(const Texture &) = delete;
  Texture &operator=(const Texture &) = delete;
  Texture(Texture &&other) noexcept;
  Texture &operator=(Texture &&other) noexcept;

  bgfx::TextureHandle handle() const { return this->m_handle; }
  bool isValid() const { return bgfx::isValid(this->m_handle); }

private:
  explicit Texture(bgfx::TextureHandle handle);

  bgfx::TextureHandle m_handle = BGFX_INVALID_HANDLE;
};

} // namespace endergfx
