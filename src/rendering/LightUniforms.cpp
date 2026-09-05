#include "LightUniforms.hpp"
#include <unordered_map>

namespace endergfx::LightUniforms {

namespace {
std::unordered_map<bgfx::ViewId, Light> s_lights;
bgfx::UniformHandle s_lightDir = BGFX_INVALID_HANDLE;
bgfx::UniformHandle s_lightColor = BGFX_INVALID_HANDLE;
} // namespace

void setActive(bgfx::ViewId view, const Light &light) {
  s_lights[view] = light;
}

void applyActive(bgfx::ViewId view) {
  if (!bgfx::isValid(s_lightDir)) {
    s_lightDir = bgfx::createUniform("u_lightDir", bgfx::UniformType::Vec4);
    s_lightColor = bgfx::createUniform("u_lightColor", bgfx::UniformType::Vec4);
  }

  auto it = s_lights.find(view);
  const Light &light =
      (it != s_lights.end()) ? it->second : Light{}; // default se não setado

  float dir[4] = {light.direction()[0], light.direction()[1],
                  light.direction()[2], 0.0f};
  float color[4] = {light.color()[0], light.color()[1], light.color()[2],
                    light.ambient()};

  bgfx::setUniform(s_lightDir, dir);
  bgfx::setUniform(s_lightColor, color);
}

} // namespace endergfx::LightUniforms
