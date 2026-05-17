#define GLM_ENABLE_EXPERIMENTAL
#include "shapes.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
Car::Car(glm::vec3 spawnPoint, glm::vec2 direction) {
  for (size_t i = 0; i < 4; i++) {
    Mesh3D *wheelside1 = regularPolyFace(
        10, glm::vec3(0.0f, 0.0f, -0.07f), glm::vec3(-0.25f, 0.0f, -0.07f),
        glm::vec3(0.0f, 0.0f, -1.0f), "textures/wheel-side.png");

    Mesh3D *wheelside2 = regularPolyFace(
        10, glm::vec3(0.0f, 0.0f, 0.07f), glm::vec3(-0.25f, 0.0f, 0.07f),
        glm::vec3(0.0f, 0.0f, -1.0f), "textures/wheel-side.png");

    Mesh3D *wheelrim =
        regularPolyRim(10, 0.14f, glm::vec3(0.0f, 0.0f, -0.07f),
                       glm::vec3(0.25f, 0.0f, -0.07f),
                       glm::vec3(0.0f, 0.0f, 1.0f), "textures/wheel-top.png");

    Model *wheel = new Model();
    wheel->addMesh(wheelside1);
    wheel->addMesh(wheelside2);
    wheel->addMesh(wheelrim);
    wheels[i] = wheel;
  }

  Mesh3D *car_side1 = meshFromFile("meshes/car-side1.txt");

  Mesh3D *car_side2 = meshFromFile("meshes/car-side2.txt");

  Mesh3D *car_rim =
      rimFromMesh(car_side1->getVdata(), glm::vec3(0.0f, 0.0f, 1.0f), 1.4,
                  "textures/car-rim.png");

  Model *model = new Model();
  model->addMesh(car_side1);
  model->addMesh(car_side2);
  model->addMesh(car_rim);
  carBody = model;
  rigidbody.setPosition(spawnPoint);
  rigidbody.setForward(glm::vec3(direction.x, 0.0f, direction.y));
  rigidbody.setUp(glm::vec3(0.0f, 1.0f, 0.0f));
}
glm::vec3 directionToEuler(glm::vec3 from, glm::vec3 to) {
  from = glm::normalize(from);
  to = glm::normalize(to);

  glm::quat q = glm::rotation(from, to);

  glm::vec3 euler = glm::eulerAngles(q);

  return glm::degrees(euler);
}
void Car::handleInput(Input input) {
  glm::vec3 right = glm::cross(rigidbody.getForward(), rigidbody.getUp());
  rigidbody.applyForce(
      input.power *
      (rigidbody.getForward() * std::cos(glm::radians(input.steeringAngle)) +
       right * std::sin(glm::radians(input.steeringAngle))));
}
void Car::preDraw() {
  glm::vec3 rotn =
      directionToEuler(glm::vec3(-1.0f, 0.0f, 0.0f), rigidbody.getForward());
  carBody->reset();
  carBody->applyRotn(rotn);
  carBody->applyTranslation(rigidbody.getPosition());
  for (int i = 0; i < 4; i++) {
    wheels[i]->reset();
    wheels[i]->applyRotn(rotn);
    wheels[i]->applyTranslation(rigidbody.getPosition());
  }
  glm::vec3 right = glm::cross(rigidbody.getForward(), rigidbody.getUp());
  wheels[0]->applyTranslation(rigidbody.getForward() * 1.15f +
                              rigidbody.getUp() * -0.27f + right * 0.7f);
  wheels[1]->applyTranslation(rigidbody.getForward() * 1.15f +
                              rigidbody.getUp() * -0.27f + right * -0.7f);
  wheels[2]->applyTranslation(rigidbody.getForward() * -1.04f +
                              rigidbody.getUp() * -0.27f + right * 0.7f);
  wheels[3]->applyTranslation(rigidbody.getForward() * -1.04f +
                              rigidbody.getUp() * -0.27f + right * -0.7f);
}
