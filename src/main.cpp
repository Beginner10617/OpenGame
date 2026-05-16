#include "game.hpp"
#include "shapes.hpp"
#include <iostream>
int main() {
  Game game(1280, 720, "Game");
  game.CreateGraphicsPipeline("shaders/vshader.glsl", "shaders/fshader.glsl");
  const int FPS = 60;
  const float frameDelay = 1000.0f / FPS;

  Model *carmodel = car();
  Mesh3D *grnd = ground(-0.5f, -10, -10, 20, 20, "textures/ground_texture.jpg");
  game.addModel(carmodel);
  game.addMesh(grnd);
  carmodel->applyTranslation(glm::vec3(0.0f, 0.0f, -5.5f));
  Uint32 lastTicks = SDL_GetTicks();
  while (game.getIsRunning()) {
    Uint32 frameStart = SDL_GetTicks();

    // Delta Time calculation
    Uint32 currentTicks = frameStart;
    float deltaTime = (currentTicks - lastTicks) / 1000.0f;
    lastTicks = currentTicks;
    carmodel->applyRotn(glm::vec3(0.0f, 30 * deltaTime, 0.0f));
    game.Render();
    game.HandleInput(deltaTime);

    // Frame Limiter
    Uint32 frameTime = SDL_GetTicks() - frameStart;

    if (frameTime < frameDelay) {
      SDL_Delay(frameDelay - frameTime);
    }
  }
}
