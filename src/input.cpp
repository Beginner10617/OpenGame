#include "game.hpp"
#include <iostream>
void Game::HandleInput() {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT)
      isRunning = false;
  }
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  Input input{0.0f, 0.0f};
  if (keystate[SDL_SCANCODE_UP]) {
    input.power += 10.0f;
  }
  if (keystate[SDL_SCANCODE_DOWN]) {
    input.power -= 10.0f;
  }
  if (keystate[SDL_SCANCODE_LEFT]) {
    input.steeringAngle -= 90.0f;
  }
  if (keystate[SDL_SCANCODE_RIGHT]) {
    input.steeringAngle += 90.0f;
  }
  player->handleInput(input);
  camera.Eye = player->rigidbody.getPosition() +
               player->rigidbody.getForward() * -2.5f +
               player->rigidbody.getUp() * 1.35f;
  camera.forwardDirection = player->rigidbody.getForward();
  camera.forwardDirection.y = 0.0f;
  camera.upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
  camera.TurnDown(20.0f);
}
