#pragma once
#include "endergfx/Light.hpp"
#include <bgfx/bgfx.h>

namespace endergfx::LightUniforms {

void setActive(bgfx::ViewId view, const Light &light);
void applyActive(bgfx::ViewId view);

} // namespace endergfx::LightUniforms
