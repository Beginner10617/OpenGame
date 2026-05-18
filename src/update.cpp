#include "game.hpp"
void Game::Update(float dt) {

  player->rigidbody.update(dt);

  // friction
  float maxFriction = 2.0f;
  if (glm::length(player->rigidbody.getSpeed()) > 1e-1) {
    player->rigidbody.applyForce(
        maxFriction * -glm::normalize(player->rigidbody.getForward()));
    player->rigidbody.stationary = false;
  } else if (!player->rigidbody.stationary) {
    player->rigidbody.stop();
  }
}
