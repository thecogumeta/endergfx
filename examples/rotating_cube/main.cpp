#include <endergfx/Camera.hpp>
#include <endergfx/Input.hpp>
#include <endergfx/Mesh.hpp>
#include <endergfx/Model.hpp>
#include <endergfx/Renderer.hpp>
#include <endergfx/Window.hpp>

#include <vector>

int main() {
  endergfx::WindowConfig config;
  config.title = "endergfx - rotating cube";
  config.width = 1280;
  config.height = 720;

  endergfx::Window window(config);
  endergfx::Input input;
  endergfx::Renderer renderer(window, config.width, config.height);

  endergfx::Camera camera;
  camera.setPosition(0.0f, 0.0f, -5.0f);
  camera.lookAt(0.0f, 0.0f, 0.0f);
  camera.setPerspective(60.0f,
                        static_cast<float>(config.width) /
                            static_cast<float>(config.height),
                        0.1f, 100.0f);

  std::vector<endergfx::Vertex> vertices = {
      {-1.0f, 1.0f, 1.0f, 0xff000000},   {1.0f, 1.0f, 1.0f, 0xff0000ff},
      {-1.0f, -1.0f, 1.0f, 0xff00ff00},  {1.0f, -1.0f, 1.0f, 0xff00ffff},
      {-1.0f, 1.0f, -1.0f, 0xffff0000},  {1.0f, 1.0f, -1.0f, 0xffff00ff},
      {-1.0f, -1.0f, -1.0f, 0xffffff00}, {1.0f, -1.0f, -1.0f, 0xffffffff},
  };

  std::vector<uint16_t> indices = {
      0, 1, 2, 1, 3, 2, 4, 6, 5, 5, 6, 7, 0, 2, 4, 4, 2, 6,
      1, 5, 3, 5, 7, 3, 0, 4, 1, 4, 5, 1, 2, 3, 6, 6, 3, 7,
  };

  endergfx::Mesh cubeMesh(vertices, indices);
  endergfx::Model cube(cubeMesh);

  float angle = 0.0f;

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

    angle += 0.01f;
    cube.setRotation(angle * 20.0f, angle * 40.0f, 0.0f);

    renderer.setCamera(0, camera);
    renderer.beginFrame();
    cube.draw(0);
    renderer.endFrame();
  }

  return 0;
}
