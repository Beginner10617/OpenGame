#ifndef GAME_HPP
#define GAME_HPP
#include "SDL.h"
#include "camera.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include <glad/glad.h>
class Game {
public:
  Game(int screenwidth, int screenheight, const char *title);
  void CreateGraphicsPipeline(const char *vShader, const char *fShader);
  void HandleInput(float deltaTime);
  void Update(float deltaTime);
  void Render();
  ~Game();
  bool getIsRunning();
  void addMesh(Mesh3D *mesh);
  void clearMeshes();
  void addModel(Model *model);

private:
  int screenwidth;
  int screenheight;
  SDL_Window *window;
  SDL_GLContext openGLContext;
  bool isRunning;
  GLuint graphicsPipeline;
  Camera camera;
  std::vector<Mesh3D *> meshes;
};
#endif
