#include "game.hpp"
#include "shapes.hpp"
#include <iostream>
int main() {
  Game game(1280, 720, "Game");
  game.CreateGraphicsPipeline("/Users/zain/openGL/shaders/vshader.glsl",
                              "/Users/zain/openGL/shaders/fshader.glsl");
  //  Mesh3D mesh{{-0.5f, -0.5f, -5.0f, 0.0f,  0.0f, 0.5f,  -0.5f,
  //               -5.0f, 1.0f,  0.0f,  0.5f,  0.5f, -5.0f, 1.0f,
  //               1.0f,  -0.5f, 0.5f,  -5.0f, 0.0f, 1.0f},
  //              {0, 1, 2, 2, 3, 0},
  //              "/Users/zain/openGL/textures/stone-wall.jpg"};

  Model *model = car();
  game.addModel(model);
  model->applyTranslation(glm::vec3(0.0f, 0.0f, -5.5f));
  Uint32 lastTicks = SDL_GetTicks();
  while (game.getIsRunning()) {
    Uint32 frameStart = SDL_GetTicks();

    // Delta Time calculation
    Uint32 currentTicks = frameStart;
    float deltaTime = (currentTicks - lastTicks) / 1000.0f;
    lastTicks = currentTicks;

    model->applyRotn(glm::vec3(0.0f, 0.01f, 0.0f));
    game.Render();
    game.HandleInput();

    // Frame Limiter
    Uint32 frameTime = SDL_GetTicks() - frameStart;

    if (frameTime < frameDelay) {
      SDL_Delay(frameDelay - frameTime);
    }
  }
}
