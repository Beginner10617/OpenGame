#include "game.hpp"
#include <iostream>
void Game::Update(float dt) {

  player->rigidbody.update(dt);

  // friction
  float maxFriction = tileBelowPlayer() == 'R' ? 2.0f : 7.5f;
  if (glm::length(player->rigidbody.getSpeed()) > 1e-1) {
    player->rigidbody.applyForce(
        maxFriction * -glm::normalize(player->rigidbody.getForward()));
    player->rigidbody.stationary = false;
  } else if (!player->rigidbody.stationary) {
    player->rigidbody.stop();
  }
}
