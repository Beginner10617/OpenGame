#include "game.hpp"
#include <iostream>
int main() {
  Game game(1280, 720, "Game");
  game.CreateGraphicsPipeline("/Users/zain/openGL/shaders/vshader.glsl",
                              "/Users/zain/openGL/shaders/fshader.glsl");
  Mesh3D mesh{{-0.5f, -0.5f, -1.0f, 0.0f,  0.0f, 0.5f,  -0.5f,
               -1.0f, 1.0f,  0.0f,  0.5f,  0.5f, -1.0f, 1.0f,
               1.0f,  -0.5f, 0.5f,  -1.0f, 0.0f, 1.0f},
              {0, 1, 2, 2, 3, 0},
              "/Users/zain/openGL/textures/stone-wall.jpg"};
  game.addMesh(&mesh);
  while (game.getIsRunning()) {
    game.Render();
    game.HandleInput();
  }
}
