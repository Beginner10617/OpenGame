#include "camera.hpp"
#include "glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
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
glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(Eye, Eye + forwardDirection, upDirection);
}
glm::mat4 Camera::getProjection() const {
  return glm::perspective(glm::radians(FOV), aspect, near, far);
}
void Camera::MoveForward(float dist) { Eye += forwardDirection * dist; }
void Camera::MoveBackward(float dist) { Eye -= forwardDirection * dist; }
void Camera::MoveUp(float dist) { Eye += upDirection * dist; }
void Camera::MoveDown(float dist) { Eye -= upDirection * dist; }
void Camera::MoveLeft(float dist) {
  glm::vec3 left = glm::cross(upDirection, forwardDirection);
  Eye += left * dist;
}
void Camera::MoveRight(float dist) {
  glm::vec3 right = glm::cross(forwardDirection, upDirection);
  Eye += right * dist;
}

void Camera::TurnUp(float angle) {
  glm::vec3 right = glm::cross(forwardDirection, upDirection);
  forwardDirection = glm::rotate(forwardDirection, glm::radians(angle), right);
  upDirection = glm::normalize(cross(right, forwardDirection));
}
void Camera::TurnDown(float angle) {
  glm::vec3 right = glm::cross(forwardDirection, upDirection);
  forwardDirection = glm::rotate(forwardDirection, -glm::radians(angle), right);
  upDirection = glm::normalize(cross(right, forwardDirection));
}
void Camera::TurnRight(float angle) {
  forwardDirection =
      glm::rotate(forwardDirection, -glm::radians(angle), upDirection);
}
void Camera::TurnLeft(float angle) {
  forwardDirection =
      glm::rotate(forwardDirection, glm::radians(angle), upDirection);
}
void Camera::TwistRight(float angle) {
  upDirection = glm::rotate(upDirection, glm::radians(angle), forwardDirection);
}
void Camera::TwistLeft(float angle) {
  upDirection =
      glm::rotate(upDirection, -glm::radians(angle), forwardDirection);
}
