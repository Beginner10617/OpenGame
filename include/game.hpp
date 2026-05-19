#ifndef GAME_HPP
#define GAME_HPP
#include "SDL.h"
#include "camera.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "shapes.hpp"
#include <glad/glad.h>
#include <map>
#include <unordered_map>
class Game {
public:
  Game(int screenwidth, int screenheight, const char *title);
  void CreateGraphicsPipeline(const char *vShader, const char *fShader);
  void HandleInput();
  void Update(float deltaTime);
  void Render();
  ~Game();
  bool getIsRunning();
  size_t addMesh(Mesh3D *mesh);
  void clearMeshes();
  size_t addModel(Model *model);
  void removeMesh(size_t index);
  std::pair<int, int> getPlayerBlock();
  void setMapData(std::map<std::pair<int, int>, char> &data,
                  float scale = 1.0f);
  char tileBelowPlayer();

private:
  int screenwidth;
  int screenheight;
  SDL_Window *window;
  SDL_GLContext openGLContext;
  bool isRunning;
  GLuint graphicsPipeline;
  Camera camera;
  std::vector<Mesh3D *> meshes;
  std::map<std::pair<int, int>, char> mapData;
  float mapscale;
  Car *player;
};
#endif
