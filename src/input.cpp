#include "game.hpp"
void Game::HandleInput(float deltatime) {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT)
      isRunning = false;
  }
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  float deltaX = 1.0f * deltatime, deltaA = 10.0f * deltatime;
  if (keystate[SDL_SCANCODE_W])
    camera.MoveForward(deltaX);
  if (keystate[SDL_SCANCODE_S])
    camera.MoveBackward(deltaX);
  if (keystate[SDL_SCANCODE_A])
    camera.MoveLeft(deltaX);
  if (keystate[SDL_SCANCODE_D])
    camera.MoveRight(deltaX);
  if (keystate[SDL_SCANCODE_Q])
    camera.MoveUp(deltaX);
  if (keystate[SDL_SCANCODE_E])
    camera.MoveDown(deltaX);
  if (keystate[SDL_SCANCODE_I] || keystate[SDL_SCANCODE_UP])
    camera.TurnUp(deltaA);
  if (keystate[SDL_SCANCODE_K] || keystate[SDL_SCANCODE_DOWN])
    camera.TurnDown(deltaA);
  if (keystate[SDL_SCANCODE_J] || keystate[SDL_SCANCODE_LEFT])
    camera.TurnLeft(deltaA);
  if (keystate[SDL_SCANCODE_L] || keystate[SDL_SCANCODE_RIGHT])
    camera.TurnRight(deltaA);
  if (keystate[SDL_SCANCODE_U])
    camera.TwistLeft(deltaA);
  if (keystate[SDL_SCANCODE_O])
    camera.TwistRight(deltaA);
}
