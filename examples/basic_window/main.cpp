#include <endergfx/Input.hpp>
#include <endergfx/Renderer.hpp>
#include <endergfx/Window.hpp>

int main() {
  endergfx::WindowConfig winConfig;
  winConfig.title = "endergfx - basic window";
  winConfig.width = 1280;
  winConfig.height = 720;

  endergfx::Window window(winConfig);
  endergfx::Renderer renderer(window, winConfig.width, winConfig.height);
  endergfx::Input input;

  if (!window.isRunning()) {
    return 1;
  }

  SDL_Event event;
  while (window.isRunning()) {
    input.resetFrameState();
    while (SDL_PollEvent(&event)) {
      window.handleEvent(event);
      input.handleEvent(event);
    }

    if (input.isKeyDown(SDL_SCANCODE_ESCAPE)) {
      break;
    }

    renderer.beginFrame();
    renderer.endFrame();
  }

  return 0;
}
