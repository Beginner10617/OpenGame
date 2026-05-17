#include <iostream>
#include "game.hpp"
void Game::HandleInput(float deltatime) {
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
    player->rigidbody.getForward() * -3.5f +
    player->rigidbody.getUp() * 0.5f;

  // friction
  float maxFriction = 2.0f;
  if(glm::length(player->rigidbody.getSpeed()) > 1e-1){
    player->rigidbody.applyForce(maxFriction *
      -glm::normalize(player->rigidbody.getForward()));
    player->rigidbody.stationary = false;}
  else if (!player->rigidbody.stationary) {
    std::cout << "stopping\n";
    player->rigidbody.stop();
  }
}
