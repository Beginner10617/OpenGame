#include "game.hpp"
#include "shapes.hpp"
#include <iostream>
int main() {
  Game game(1280, 720, "Game");
  game.CreateGraphicsPipeline("/Users/zain/openGL/shaders/vshader.glsl",
                              "/Users/zain/openGL/shaders/fshader.glsl");
  const int FPS = 60;
  const float frameDelay = 1000.0f / FPS;

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
    model->applyRotn(glm::vec3(0.0f, 30 * deltaTime, 0.0f));
    game.Render();
    game.HandleInput(deltaTime);

    // Frame Limiter
    Uint32 frameTime = SDL_GetTicks() - frameStart;

    if (frameTime < frameDelay) {
      SDL_Delay(frameDelay - frameTime);
    }
  }
}
