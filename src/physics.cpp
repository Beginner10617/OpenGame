#define GLM_ENABLE_EXPERIMENTAL
#include "physics.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

Rigidbody::Rigidbody(float Mass) {
  mass = Mass;
  maxVel = 100.0f;
  stationary = true;
}

void Rigidbody::setPosition(glm::vec3 posn) { position = posn; }
void Rigidbody::setForward(glm::vec3 fwd) { forward = fwd; }
void Rigidbody::setUp(glm::vec3 Up) { up = Up; }

glm::vec3 Rigidbody::getVelocity(){return velocity;};
glm::vec3 Rigidbody::getPosition() { return position; }
glm::vec3 Rigidbody::getForward() { return forward; }
glm::vec3 Rigidbody::getUp() { return up; }
float Rigidbody::getSpeed() {return glm::length(velocity);}
void Rigidbody::stop(){
  velocity = glm::vec3(0.0f);
  stationary = true;
}
void Rigidbody::applyForce(glm::vec3 force) { netForce += force; }
void Rigidbody::update(float dt) {
  velocity += netForce * dt / mass;
  if (glm::length(velocity) > maxVel)
    velocity = maxVel * glm::normalize(velocity);
  netForce = glm::vec3(0.0f);
  position += velocity * dt;
  if(glm::length(velocity) > 1.0f){
    forward = glm::normalize(glm::vec3(velocity.x, 0.0f, velocity.z));
  }
}
