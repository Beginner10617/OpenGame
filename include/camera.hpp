#ifndef CAMERA
#define CAMERA
#include "glm/glm.hpp"
class Camera {
public:
  Camera();
  Camera(glm::vec3 eye);
  ~Camera();

  glm::mat4 getViewMatrix() const;

  void MoveForward(float dist);
  void MoveBackward(float dist);
  void MoveLeft(float dist);
  void MoveRight(float dist);
  void MoveUp(float dist);
  void MoveDown(float dist);

  void TurnUp(float angle); // angle presumed in degrees
  void TurnDown(float angle);
  void TurnLeft(float angle);
  void TurnRight(float angle);

private:
  glm::vec3 Eye;
  glm::vec3 forwardDirection;
  glm::vec3 upDirection;
};
#endif
