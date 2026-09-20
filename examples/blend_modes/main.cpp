#include <endergfx/endergfx.hpp>
#include <memory>
#include <vector>

int main() {
  endergfx::WindowConfig config;
  config.title = "endergfx - blend modes";
  config.width = 1280;
  config.height = 720;

  endergfx::Window window(config);
  endergfx::Input input;
  endergfx::Renderer renderer(window, config.width, config.height);

  endergfx::Camera camera;
  camera.setPosition(0.0f, 0.0f, -15.0f);
  camera.lookAt(0.0f, 0.0f, 0.0f);
  camera.setPerspective(60.0f,
                        static_cast<float>(config.width) /
                            static_cast<float>(config.height),
                        0.1f, 100.0f);

  std::vector<endergfx::Vertex> vertices = {
      {.x = -1.0f,
       .y = 1.0f,
       .z = 1.0f,
       .nx = 0.0f,
       .ny = 0.0f,
       .nz = 1.0f,
       .abgr = 0xff000000},
      {.x = 1.0f,
       .y = 1.0f,
       .z = 1.0f,
       .nx = 0.0f,
       .ny = 0.0f,
       .nz = 1.0f,
       .abgr = 0xff0000ff},
      {.x = -1.0f,
       .y = -1.0f,
       .z = 1.0f,
       .nx = 0.0f,
       .ny = 0.0f,
       .nz = 1.0f,
       .abgr = 0xff00ff00},
      {.x = 1.0f,
       .y = -1.0f,
       .z = 1.0f,
       .nx = 0.0f,
       .ny = 0.0f,
       .nz = 1.0f,
       .abgr = 0xff00ffff},
      {.x = -1.0f,
       .y = 1.0f,
       .z = -1.0f,
       .nx = 0.0f,
       .ny = 0.0f,
       .nz = -1.0f,
       .abgr = 0xffff0000},
      {.x = -1.0f,
       .y = -1.0f,
       .z = -1.0f,
       .nx = 0.0f,
       .ny = 0.0f,
       .nz = -1.0f,
       .abgr = 0xffffff00},
      {.x = 1.0f,
       .y = 1.0f,
       .z = -1.0f,
       .nx = 0.0f,
       .ny = 0.0f,
       .nz = -1.0f,
       .abgr = 0xffff00ff},
      {.x = 1.0f,
       .y = -1.0f,
       .z = -1.0f,
       .nx = 0.0f,
       .ny = 0.0f,
       .nz = -1.0f,
       .abgr = 0xffffffff},
      {.x = -1.0f,
       .y = 1.0f,
       .z = 1.0f,
       .nx = -1.0f,
       .ny = 0.0f,
       .nz = 0.0f,
       .abgr = 0xff000000},
      {.x = -1.0f,
       .y = -1.0f,
       .z = 1.0f,
       .nx = -1.0f,
       .ny = 0.0f,
       .nz = 0.0f,
       .abgr = 0xff00ff00},
      {.x = -1.0f,
       .y = 1.0f,
       .z = -1.0f,
       .nx = -1.0f,
       .ny = 0.0f,
       .nz = 0.0f,
       .abgr = 0xffff0000},
      {.x = -1.0f,
       .y = -1.0f,
       .z = -1.0f,
       .nx = -1.0f,
       .ny = 0.0f,
       .nz = 0.0f,
       .abgr = 0xffffff00},
      {.x = 1.0f,
       .y = 1.0f,
       .z = 1.0f,
       .nx = 1.0f,
       .ny = 0.0f,
       .nz = 0.0f,
       .abgr = 0xff0000ff},
      {.x = 1.0f,
       .y = 1.0f,
       .z = -1.0f,
       .nx = 1.0f,
       .ny = 0.0f,
       .nz = 0.0f,
       .abgr = 0xffff00ff},
      {.x = 1.0f,
       .y = -1.0f,
       .z = 1.0f,
       .nx = 1.0f,
       .ny = 0.0f,
       .nz = 0.0f,
       .abgr = 0xff00ffff},
      {.x = 1.0f,
       .y = -1.0f,
       .z = -1.0f,
       .nx = 1.0f,
       .ny = 0.0f,
       .nz = 0.0f,
       .abgr = 0xffffffff},
      {.x = -1.0f,
       .y = 1.0f,
       .z = 1.0f,
       .nx = 0.0f,
       .ny = 1.0f,
       .nz = 0.0f,
       .abgr = 0xff000000},
      {.x = -1.0f,
       .y = 1.0f,
       .z = -1.0f,
       .nx = 0.0f,
       .ny = 1.0f,
       .nz = 0.0f,
       .abgr = 0xffff0000},
      {.x = 1.0f,
       .y = 1.0f,
       .z = 1.0f,
       .nx = 0.0f,
       .ny = 1.0f,
       .nz = 0.0f,
       .abgr = 0xff0000ff},
      {.x = 1.0f,
       .y = 1.0f,
       .z = -1.0f,
       .nx = 0.0f,
       .ny = 1.0f,
       .nz = 0.0f,
       .abgr = 0xffff00ff},
      {.x = -1.0f,
       .y = -1.0f,
       .z = 1.0f,
       .nx = 0.0f,
       .ny = -1.0f,
       .nz = 0.0f,
       .abgr = 0xff00ff00},
      {.x = 1.0f,
       .y = -1.0f,
       .z = 1.0f,
       .nx = 0.0f,
       .ny = -1.0f,
       .nz = 0.0f,
       .abgr = 0xff00ffff},
      {.x = -1.0f,
       .y = -1.0f,
       .z = -1.0f,
       .nx = 0.0f,
       .ny = -1.0f,
       .nz = 0.0f,
       .abgr = 0xffffff00},
      {.x = 1.0f,
       .y = -1.0f,
       .z = -1.0f,
       .nx = 0.0f,
       .ny = -1.0f,
       .nz = 0.0f,
       .abgr = 0xffffffff},
  };

  std::vector<uint16_t> indices = {
      0,  1,  2,  1,  3,  2,  4,  5,  6,  6,  5,  7,  8,  9,  10, 10, 9,  11,
      12, 13, 14, 13, 15, 14, 16, 17, 18, 17, 19, 18, 20, 21, 22, 22, 21, 23,
  };

  auto cubeMesh = std::make_shared<endergfx::Mesh>(vertices, indices);

  auto matOpaque =
      std::make_shared<endergfx::Material>(endergfx::MaterialProperties{
          .baseTexture =
              endergfx::Texture::createSolidColor(255, 255, 255, 255),
          .blendMode = endergfx::BlendMode::Opaque,
      });
  auto matTransparent =
      std::make_shared<endergfx::Material>(endergfx::MaterialProperties{
          .baseTexture =
              endergfx::Texture::createSolidColor(255, 255, 255, 255),
          .blendMode = endergfx::BlendMode::Transparent,
          .opacity = 0.5f,
      });
  auto matAdditive =
      std::make_shared<endergfx::Material>(endergfx::MaterialProperties{
          .baseTexture = endergfx::Texture::createSolidColor(255, 255, 0, 255),
          .blendMode = endergfx::BlendMode::Additive,
      });
  auto matMultiply =
      std::make_shared<endergfx::Material>(endergfx::MaterialProperties{
          .baseTexture = endergfx::Texture::createSolidColor(32, 32, 32, 255),
          .blendMode = endergfx::BlendMode::Multiply,
      });
  auto matScreen =
      std::make_shared<endergfx::Material>(endergfx::MaterialProperties{
          .baseTexture =
              endergfx::Texture::createSolidColor(255, 255, 255, 255),
          .blendMode = endergfx::BlendMode::Screen,
      });

  endergfx::Model cubeOpaque(cubeMesh, matOpaque);
  endergfx::Model cubeTransparent(cubeMesh, matTransparent);
  endergfx::Model cubeAdditive(cubeMesh, matAdditive);
  endergfx::Model cubeMultiply(cubeMesh, matMultiply);
  endergfx::Model cubeScreen(cubeMesh, matScreen);

  float positions[] = {-8.0f, -4.0f, 0.0f, 4.0f, 8.0f};
  cubeOpaque.setPosition(positions[0], 0.0f, 0.0f);
  cubeTransparent.setPosition(positions[1], 0.0f, 0.0f);
  cubeAdditive.setPosition(positions[2], 0.0f, 0.0f);
  cubeMultiply.setPosition(positions[3], 0.0f, 0.0f);
  cubeScreen.setPosition(positions[4], 0.0f, 0.0f);

  float angle = 0.0f;

  SDL_Event event;
  while (window.isRunning()) {
    while (SDL_PollEvent(&event)) {
      window.handleEvent(event);
      input.handleEvent(event);
    }

    if (input.isKeyDown(SDL_SCANCODE_ESCAPE)) {
      break;
    }

    angle += 0.01f;
    cubeOpaque.setRotation(angle * 20.0f, angle * 40.0f, 0.0f);
    cubeTransparent.setRotation(angle * 20.0f, angle * 40.0f, 0.0f);
    cubeAdditive.setRotation(angle * 20.0f, angle * 40.0f, 0.0f);
    cubeMultiply.setRotation(angle * 20.0f, angle * 40.0f, 0.0f);
    cubeScreen.setRotation(angle * 20.0f, angle * 40.0f, 0.0f);

    renderer.setCamera(0, camera);
    renderer.beginFrame();
    cubeOpaque.draw(0);
    cubeTransparent.draw(0);
    cubeAdditive.draw(0);
    cubeMultiply.draw(0);
    cubeScreen.draw(0);
    renderer.endFrame();
  }

  return 0;
}
