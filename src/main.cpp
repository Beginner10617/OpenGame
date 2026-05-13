#include "game.hpp"
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

  Mesh3D mesh1{
    {
    (a-0.5f)*0.5f, -0.25f, -0.07f, a, 0.0f,
    (0.5f-a)*0.5f, -0.25f, -0.07f, 1.0f-a, 0.0f,
    0.25f, (a-0.5f) *0.5f, -0.07f, 1.0f, a,
    0.25f, (0.5f-a) *0.5f, -0.07f, 1.0f, 1.0f-a,
    (0.5f-a) *0.5f, 0.25f, -0.07f, 1.0f-a, 1.0f,
    (a-0.5f) *0.5f, 0.25f, -0.07f, a, 1.0f,
    -0.25f, (0.5f-a)*0.5f, -0.07f, 0.0f, 1.0f-a,
    -0.25f, (a-0.5f)*0.5f, -0.07f, 0.0f, a
    },
    {0, 1, 4, 4, 5, 0, 1, 2, 3, 3, 4, 1, 0, 5, 7, 7, 5, 6},
    "/Users/zain/openGL/textures/wheel-side.png"
  };

  Mesh3D mesh2{
    {
    (a-0.5f)*0.5f, -0.25f, 0.07f, a, 0.0f,
    (0.5f-a)*0.5f, -0.25f, 0.07f, 1.0f-a, 0.0f,
    0.25f, (a-0.5f) *0.5f, 0.07f, 1.0f, a,
    0.25f, (0.5f-a) *0.5f, 0.07f, 1.0f, 1.0f-a,
    (0.5f-a) *0.5f, 0.25f, 0.07f, 1.0f-a, 1.0f,
    (a-0.5f) *0.5f, 0.25f, 0.07f, a, 1.0f,
    -0.25f, (0.5f-a)*0.5f, 0.07f, 0.0f, 1.0f-a,
    -0.25f, (a-0.5f)*0.5f, 0.07f, 0.0f, a
    },
    {0, 1, 4, 4, 5, 0, 1, 2, 3, 3, 4, 1, 0, 5, 7, 7, 5, 6},
    "/Users/zain/openGL/textures/wheel-side.png"
  };
  
  Model model;
  model.addMesh(&mesh1);
  model.addMesh(&mesh2);
  game.addModel(&model);
  model.applyTranslation(glm::vec3(0.0f,0.0f,-5.0f));
  model.applyRotn(glm::vec3(0.0f, 90.0f, 0.0f));
  while (game.getIsRunning()) {
    game.Render();
    game.HandleInput();
  }
}
