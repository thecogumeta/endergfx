#include "ShaderUtils.hpp"
#include "endergfx/Log.hpp"

#include "essl/model_fs.sc.bin.h"
#include "essl/model_vs.sc.bin.h"
#include "glsl/model_fs.sc.bin.h"
#include "glsl/model_vs.sc.bin.h"
#include "spirv/model_fs.sc.bin.h"
#include "spirv/model_vs.sc.bin.h"
#include <bgfx/bgfx.h>

namespace endergfx::ShaderUtils {

namespace {

bgfx::ShaderHandle
createShaderForCurrentRenderer(const uint8_t *glsl, uint32_t glslSize,
                               const uint8_t *essl, uint32_t esslSize,
                               const uint8_t *spv, uint32_t spvSize) {
  const uint8_t *data = nullptr;
  uint32_t size = 0;

  switch (bgfx::getRendererType()) {
  case bgfx::RendererType::OpenGL:
    data = glsl;
    size = glslSize;
    break;
  case bgfx::RendererType::OpenGLES:
    data = essl;
    size = esslSize;
    break;
  case bgfx::RendererType::Vulkan:
    data = spv;
    size = spvSize;
    break;
  default:
    return BGFX_INVALID_HANDLE;
  }

  return bgfx::createShader(bgfx::copy(data, size));
}

} // namespace

bgfx::ProgramHandle createDefaultProgram() {
  bgfx::ShaderHandle vsh = createShaderForCurrentRenderer(
      model_vs_glsl, sizeof(model_vs_glsl), model_vs_essl,
      sizeof(model_vs_essl), model_vs_spv, sizeof(model_vs_spv));

  bgfx::ShaderHandle fsh = createShaderForCurrentRenderer(
      model_fs_glsl, sizeof(model_fs_glsl), model_fs_essl,
      sizeof(model_fs_essl), model_fs_spv, sizeof(model_fs_spv));

  if (!bgfx::isValid(vsh) || !bgfx::isValid(fsh)) {
    log(LogLevel::Error,
        "Failed to create default shader program (unsupported renderer?)");
    if (bgfx::isValid(vsh))
      bgfx::destroy(vsh);
    if (bgfx::isValid(fsh))
      bgfx::destroy(fsh);
    return BGFX_INVALID_HANDLE;
  }

  return bgfx::createProgram(vsh, fsh, true);
}

} // namespace endergfx::ShaderUtils
