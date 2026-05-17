#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include "shapes.hpp"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
Car::Car(glm::vec3 spawnPoint, glm::vec2 direction, Game& game) {
  for (size_t i = 0; i < 4; i++) {
    Mesh3D *wheelside1 = regularPolyFace(
        10, glm::vec3(0.0f, 0.0f, -0.07f), glm::vec3(-0.25f, 0.0f, -0.07f),
        glm::vec3(0.0f, 0.0f, -1.0f), "textures/wheel-side.png");

    Mesh3D *wheelside2 = regularPolyFace(
        10, glm::vec3(0.0f, 0.0f, 0.07f), glm::vec3(-0.25f, 0.0f, 0.07f),
        glm::vec3(0.0f, 0.0f, -1.0f), "textures/wheel-side.png");

    Mesh3D *wheelrim = regularPolyRim(
        10, 0.14f, glm::vec3(0.0f, 0.0f, -0.07f), glm::vec3(0.25f, 0.0f, -0.07f),
        glm::vec3(0.0f, 0.0f, 1.0f), "textures/wheel-top.png");

    Model *wheel = new Model();
    wheel->addMesh(wheelside1);
    wheel->addMesh(wheelside2);
    wheel->addMesh(wheelrim);
    wheels[i] = wheel;
    game.addModel(wheels[i]);
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
  game.addModel(model);
  carBody = model;
  position = spawnPoint;
  forward = glm::vec3(direction.x, 0.0f, direction.y);
  up = glm::vec3(0.0f, 1.0f, 0.0f);
}
glm::vec3 directionToEuler(glm::vec3 from, glm::vec3 to) {
  from = glm::normalize(from);
  to = glm::normalize(to);

  glm::quat q = glm::rotation(from, to);

  glm::vec3 euler = glm::eulerAngles(q);

  return glm::degrees(euler);
}

void Car::preDraw() {
  glm::vec3 rotn = directionToEuler(glm::vec3(-1.0f, 0.0f, 0.0f), forward);
  carBody->reset();
  carBody->applyRotn(rotn);
  carBody->applyTranslation(position);
  for (int i = 0; i < 4; i++){
    wheels[i]->reset();
    wheels[i]->applyRotn(rotn);
    wheels[i]->applyTranslation(position);
  }
  glm::vec3 right = glm::cross(forward, up);
  wheels[0]->applyTranslation(
    forward * 1.15f +
    up * -0.27f +
    right * 0.7f
  );
  wheels[1]->applyTranslation(
    forward * 1.15f +
    up * -0.27f +
    right * -0.7f
  );
  wheels[2]->applyTranslation(
    forward * -1.04f +
    up * -0.27f +
    right * 0.7f
  );
  wheels[3]->applyTranslation(
    forward * -1.04f +
    up * -0.27f +
    right * -0.7f
  );
}
