#ifndef GAME
#define GAME
#include "camera.hpp"
#include <SDL.h>
class Game {
public:
  Game(int screenwidth, int screenheight);
  HandleInput();
  Update(float deltaTime);
  Render();
  ~Game();

private:
  int screenwidth;
  int screenheight;
  SDL_Window *window;
  SDL_GLContext openGLContext;
  bool isRunning;
  GLuint graphicsPipeline;
  Camera camera;
}
#endif
