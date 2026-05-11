#include "camera.hpp"
Camera::Camera() {
  Eye = glm::vec3(0.0f, 0.0f, 0.0f);
  forwardDirection = glm::vec3(0.0f, 0.0f, -1.0f);
  upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
  FOV = 90.0f; // in degrees
  aspect = 16.0 / 9.0;
  near = 0.1f;
  far = 100.0f;
}
Camera::~Camera() {}
glm::mat4 Camera::getViewMatrix() {
  glm::mat4 projection = glm::perspective(glm::radians(FOV), aspect, near, far);
}
void MoveForward(float dist) { Eye += forwardDirection * dist; }
void MoveBackward(float dist) { Eye -= forwardDirection * dist; }
void MoveUp(float dist) { Eye += upDirection * dist; }
void MoveDown(float dist) { Eye -= upDirection * dist; }
void MoveLeft(float dist) {
  glm::vec3 left = glm::cross(upDirection, forwardDirection);
  Eye += left * dist;
}
void MoveRight(float dist) {
  glm::vec3 right = glm::cross(forwardDirection, upDirection);
  Eye += right * dist;
}
