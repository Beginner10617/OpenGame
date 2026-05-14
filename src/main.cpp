#include "game.hpp"
#include "shapes.hpp"
#include <iostream>
int main() {
  Game game(1280, 720, "Game");
  game.CreateGraphicsPipeline("/Users/zain/openGL/shaders/vshader.glsl",
                              "/Users/zain/openGL/shaders/fshader.glsl");
  const float a = 0.2928f;
  Mesh3D mesh{{-0.5f, -0.5f, -5.0f, 0.0f,  0.0f, 0.5f,  -0.5f,
               -5.0f, 1.0f,  0.0f,  0.5f,  0.5f, -5.0f, 1.0f,
               1.0f,  -0.5f, 0.5f,  -5.0f, 0.0f, 1.0f},
              {0, 1, 2, 2, 3, 0},
              "/Users/zain/openGL/textures/stone-wall.jpg"};

  Model *model = car();
  game.addModel(model);
  model->applyTranslation(glm::vec3(0.0f, 0.0f, -5.0f));
  while (game.getIsRunning()) {
    model->applyRotn(glm::vec3(0.0f,0.01f,0.0f));
    game.Render();
    game.HandleInput();
  }
}
