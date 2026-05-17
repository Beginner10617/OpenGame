#define GLM_ENABLE_EXPERIMENTAL
#include "physics.hpp"
#include <glm/gtx/rotate_vector.hpp>

Rigidbody::Rigidbody(float Mass, float MomentOfInertia) {
  mass = Mass;
  momentOfInertia = MomentOfInertia;
  maxVel = 100.0f;
  maxAngVel = 90.0f;
}

void Rigidbody::setPosition(glm::vec3 posn) { position = posn; }
void Rigidbody::setForward(glm::vec3 fwd) { forward = fwd; }
void Rigidbody::setUp(glm::vec3 Up) { up = Up; }

glm::vec3 Rigidbody::getPosition() { return position; }
glm::vec3 Rigidbody::getForward() { return forward; }
glm::vec3 Rigidbody::getUp() { return up; }

void Rigidbody::applyForce(glm::vec3 force, glm::vec3 pointOfApp) {
  netForce += force;
  netTorque += glm::cross(pointOfApp, force);
}
void Rigidbody::update(float dt) {
  velocity += netForce * dt / mass;
  if (glm::length(velocity) > maxVel)
    velocity = maxVel * glm::normalize(velocity);
  angVelocity += netTorque * dt / momentOfInertia;
  if (glm::length(angVelocity) > maxAngVel)
    angVelocity = maxAngVel * glm::normalize(angVelocity);
  netForce = glm::vec3(0.0f);
  netTorque = glm::vec3(0.0f);

  position += velocity * dt;

  float angle = glm::length(angVelocity) * dt;
  if (angle < 1e-6)
    return;

  glm::vec3 axis = glm::normalize(angVelocity);

  glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, axis);
  forward = glm::normalize(glm::vec3(rotation * glm::vec4(forward, 0.0f)));
  up = glm::normalize(glm::vec3(rotation * glm::vec4(up, 0.0f)));

  glm::vec3 right = glm::normalize(glm::cross(forward, up));
  up = glm::normalize(glm::cross(right, forward));
}
