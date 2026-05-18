#include "game.hpp"
#include "shapes.hpp"
#include "map.hpp"
#include <iostream>
int main() {
  Game game(1280, 720, "Game");
  game.CreateGraphicsPipeline("shaders/vshader.glsl", "shaders/fshader.glsl");
  const int FPS = 60;
  const float frameDelay = 1000.0f / FPS;
  
  std::map<std::pair<int, int>, char> mData;
  mData[{0,0}]='R';
  mData[{0,1}]='R';
  mData[{1,0}]='R';
  mData[{1,1}]='R';
  std::map<char, struct Tile> tileInfo;
  tileInfo['R']={glm::vec2(0.0f,0.0f), glm::vec2(1.0f, 0.5f)};
  Map map{mData, "textures/atlas.png",tileInfo, -2.5f};
  
  Mesh3D *grnd = map.getMesh();

  game.addMesh(grnd);
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
