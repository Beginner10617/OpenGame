#include "game.hpp"
#include "map.hpp"
#include "shapes.hpp"
#include <iostream>
int main() {
  Game game(1280, 720, "Game");
  game.CreateGraphicsPipeline("shaders/vshader.glsl", "shaders/fshader.glsl");
  const int FPS = 60;
  const float frameDelay = 1000.0f / FPS;

  Map map{"levels/level-1.txt", -0.5f, 4.0f};

  Mesh3D *grnd = map.getMesh();

  game.addMesh(grnd);
  game.setMapData(map.data, 4.0f);
  Uint32 lastTicks = SDL_GetTicks();
  while (game.getIsRunning()) {
    Uint32 frameStart = SDL_GetTicks();

    // Delta Time calculation
    Uint32 currentTicks = frameStart;
    float deltaTime = (currentTicks - lastTicks) / 1000.0f;
    lastTicks = currentTicks;
    game.Render();
    game.HandleInput();
    game.Update(deltaTime);

    // Frame Limiter
    Uint32 frameTime = SDL_GetTicks() - frameStart;

    if (frameTime < frameDelay) {
      SDL_Delay(frameDelay - frameTime);
    }
  }
}
