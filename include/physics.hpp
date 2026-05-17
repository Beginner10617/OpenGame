#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include <glm/glm.hpp>
class Rigidbody {
public:
  Rigidbody(float Mass = 1.0f);
  void setPosition(glm::vec3 posn);
  void setForward(glm::vec3 fwd);
  void setUp(glm::vec3 Up);
  glm::vec3 getPosition();
  glm::vec3 getForward();
  glm::vec3 getUp();
  glm::vec3 getVelocity();
  float getSpeed();
  void applyForce(glm::vec3 force);
  void update(float dt);
  void stop();
  bool stationary;

private:
  glm::vec3 position, forward, up;
  glm::vec3 netForce;
  glm::vec3 velocity;
  float mass, maxVel;
};
#endif
