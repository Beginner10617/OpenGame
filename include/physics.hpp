#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include <glm/glm.hpp>
class Rigidbody {
public:
  Rigidbody(float Mass = 1.0f, float MomentOfInertia = 1.0f);
  void setPosition(glm::vec3 posn);
  void setForward(glm::vec3 fwd);
  void setUp(glm::vec3 Up);
  glm::vec3 getPosition();
  glm::vec3 getForward();
  glm::vec3 getUp();
  void applyForce(glm::vec3 force, glm::vec3 pointOfApp = glm::vec3(0.0f));
  void update(float dt);

private:
  glm::vec3 position, forward, up;
  glm::vec3 netForce, netTorque;
  glm::vec3 velocity, angVelocity;
  float mass, momentOfInertia;
};
#endif
