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

  Mesh3D *mesh1 = regularPolyFace(10, glm::vec3(0.0f, 0.0f, -0.07f),
                              glm::vec3(0.25f, (0.5f - a) * 0.5f, -0.07f),
                              glm::vec3(0.0f, 0.0f, -1.0f),
                              "/Users/zain/openGL/textures/wheel-side.png");

  Mesh3D *mesh2 = regularPolyFace(10, glm::vec3(0.0f, 0.0f, 0.07f),
                              glm::vec3(0.25f, (0.5f - a) * 0.5f, 0.07f),
                              glm::vec3(0.0f, 0.0f, -1.0f),
                              "/Users/zain/openGL/textures/wheel-side.png");
  Mesh3D *mesh3 = regularPolyRim(10, 0.14f, glm::vec3(0.0f, 0.0f, -0.07f),
                              glm::vec3(0.25f, (0.5f - a) * 0.5f, -0.07f), 
                              glm::vec3(0.0f,0.0f, 1.0f),
                              "/Users/zain/openGL/textures/wheel-top.png");

  Model model;
  model.addMesh(mesh1);
  model.addMesh(mesh2);
  model.addMesh(mesh3);
  game.addModel(&model);
  model.applyTranslation(glm::vec3(0.0f, 0.0f, -5.0f));
  while (game.getIsRunning()) {
    game.Render();
    game.HandleInput();
  }
}
