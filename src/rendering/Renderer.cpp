#include "endergfx/Renderer.hpp"
#include "LightUniforms.hpp"
#include "endergfx/Log.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_properties.h>
#include <bx/bx.h>
#include <cstdint>

namespace endergfx {

Renderer::Renderer(Window &window, unsigned int width, unsigned int height)
    : m_width(width), m_height(height) {
  SDL_PropertiesID props = SDL_GetWindowProperties(window.native());
  bgfx::PlatformData pd{};

#if BX_PLATFORM_WINDOWS
  pd.nwh = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER,
                                  nullptr);
  pd.type = bgfx::NativeWindowHandleType::Default;
#elif BX_PLATFORM_OSX
  pd.nwh = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_COCOA_WINDOW_POINTER,
                                  nullptr);
  pd.type = bgfx::NativeWindowHandleType::Default;
#else
  const char *driver = SDL_GetCurrentVideoDriver();
  if (driver && SDL_strcmp(driver, "wayland") == 0) {
    pd.ndt = SDL_GetPointerProperty(
        props, SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, nullptr);
    pd.nwh = SDL_GetPointerProperty(
        props, SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, nullptr);
    pd.type = bgfx::NativeWindowHandleType::Wayland;
  } else if (driver && SDL_strcmp(driver, "x11") == 0) {
    pd.ndt = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_X11_DISPLAY_POINTER,
                                    nullptr);
    pd.nwh = reinterpret_cast<void *>(static_cast<uintptr_t>(
        SDL_GetNumberProperty(props, SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0)));
    pd.type = bgfx::NativeWindowHandleType::Default;
  } else {
    log(LogLevel::Error, std::string("Unsupported video driver: ") +
                             (driver ? driver : "unknown"));
    return;
  }

  log(LogLevel::Debug, std::string("Detected video driver: ") + driver);
#endif

  bgfx::setPlatformData(pd);

  bgfx::Init init;
  init.type = bgfx::RendererType::Count;
  init.resolution.width = this->m_width;
  init.resolution.height = this->m_height;
  init.resolution.reset = BGFX_RESET_VSYNC;
  init.platformData = pd;

  log(LogLevel::Debug, "Initializing bgfx with resolution " +
                           std::to_string(this->m_width) + "x" +
                           std::to_string(this->m_height));
  if (!bgfx::init(init)) {
    log(LogLevel::Error, "Failed to initialize bgfx");
    return;
  }
  log(LogLevel::Debug, std::string("bgfx initialized with renderer: ") +
                           bgfx::getRendererName(bgfx::getRendererType()));

  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f,
                     0);
  bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(this->m_width),
                    static_cast<uint16_t>(this->m_height));

  this->m_valid = true;
  window.setResizeCallback([this](int w, int h) {
    this->resize(static_cast<unsigned int>(w), static_cast<unsigned int>(h));
  });
}

Renderer::~Renderer() {
  if (this->m_valid) {
    log(LogLevel::Debug, "Shutting down bgfx");
    bgfx::shutdown();
  }
}

void Renderer::resize(unsigned int width, unsigned int height) {
  if (!this->m_valid) {
    return;
  }

  this->m_width = width;
  this->m_height = height;

  bgfx::reset(static_cast<uint32_t>(width), static_cast<uint32_t>(height),
              BGFX_RESET_VSYNC);
  bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(width),
                    static_cast<uint16_t>(height));

  log(LogLevel::Debug, "Renderer resized to " + std::to_string(width) + "x" +
                           std::to_string(height));
}

void Renderer::setCamera(bgfx::ViewId view, const Camera &camera) {
  bgfx::setViewTransform(view, camera.viewMatrix(), camera.projMatrix());
}

void Renderer::setLight(bgfx::ViewId view, const Light &light) {
  LightUniforms::setActive(view, light);
}

void Renderer::beginFrame() { bgfx::touch(0); }

void Renderer::endFrame() { bgfx::frame(); }

} // namespace endergfx
