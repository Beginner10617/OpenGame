#include "game.hpp"
void Game::HandleInput(float deltatime) {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT)
      isRunning = false;
  }
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  float deltaX = 1.0f * deltatime, deltaA = 10.0f * deltatime;
  Input input{0.0f, 0.0f};
  if (keystate[SDL_SCANCODE_UP]) {
    input.power += 10.0f;
  }
  if (keystate[SDL_SCANCODE_DOWN]) {
    input.power -= 10.0f;
  }
  if (keystate[SDL_SCANCODE_LEFT]) {
    input.steeringAngle += 45.0f;
  }
  if (keystate[SDL_SCANCODE_RIGHT]) {
    input.steeringAngle -= 45.0f;
  }
  player->handleInput(input);

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
  if (keystate[SDL_SCANCODE_I])
    camera.TurnUp(deltaA);
  if (keystate[SDL_SCANCODE_K])
    camera.TurnDown(deltaA);
  if (keystate[SDL_SCANCODE_J])
    camera.TurnLeft(deltaA);
  if (keystate[SDL_SCANCODE_L])
    camera.TurnRight(deltaA);
  if (keystate[SDL_SCANCODE_U])
    camera.TwistLeft(deltaA);
  if (keystate[SDL_SCANCODE_O])
    camera.TwistRight(deltaA);
}
