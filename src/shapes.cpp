#include "shapes.hpp"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#define PI 3.14159265

Mesh3D *regularPolyFace(unsigned int sides, glm::vec3 origin, glm::vec3 vertex0,
                        glm::vec3 normal, const char *tex) {
  glm::vec3 x = glm::normalize(vertex0 - origin);
  glm::vec3 y = glm::normalize(glm::cross(x, normal));
  float radius = glm::length(vertex0 - origin);
  std::vector<GLfloat> vData{origin.x, origin.y, origin.z, 0.5f, 0.5f};
  std::vector<GLuint> iData;
  glm::vec3 pnt;
  float u, v;
  for (unsigned int i = 0; i < sides; i++) {
    pnt = origin +
          (float)std::cos((float)2 * PI * i / (float)sides) * radius * x +
          (float)std::sin((float)2 * PI * i / (float)sides) * radius * y;
    u = 0.5f + (float)std::cos((float)2 * PI * i / (float)sides) * 0.5f;
    v = 0.5f + (float)std::sin((float)2 * PI * i / (float)sides) * 0.5f;
    vData.insert(vData.end(), {pnt.x, pnt.y, pnt.z, u, v});
    iData.insert(iData.end(), {0, i + 1, (i + 2 > sides ? 1 : i + 2)});
  }
  return new Mesh3D{vData, iData, tex};
}
Mesh3D *regularPolyRim(unsigned int sides, float thickness, glm::vec3 origin,
                       glm::vec3 vertex0, glm::vec3 normal, const char *tex) {
  glm::vec3 x = glm::normalize(vertex0 - origin);
  glm::vec3 y = glm::normalize(glm::cross(x, normal));
  float radius = glm::length(vertex0 - origin);
  std::vector<GLfloat> vData;
  std::vector<GLuint> iData;
  glm::vec3 pnt1, pnt2;
  float u;

  for (unsigned int i = 0; i < sides; i++) {
    pnt1 = origin +
           (float)std::cos((float)2 * PI * i / (float)sides) * radius * x +
           (float)std::sin((float)2 * PI * i / (float)sides) * radius * y;
    pnt2 = pnt1 + normal * thickness;
    u = (float)i / (float)sides;
    vData.insert(vData.end(), {pnt1.x, pnt1.y, pnt1.z, u, 0.0f, pnt2.x, pnt2.y,
                               pnt2.z, u, 1.0f});
    iData.insert(iData.end(), {2 * i, 2 * i + 1, 2 * i + 2, 2 * i + 1,
                               2 * i + 3, 2 * i + 2});
  }
  pnt1 = origin + radius * x;
  pnt2 = pnt1 + normal * thickness;
  vData.insert(vData.end(), {pnt1.x, pnt1.y, pnt1.z, 1.0f, 0.0f, pnt2.x, pnt2.y,
                             pnt2.z, 1.0f, 1.0f});
  return new Mesh3D{vData, iData, tex};
}

enum MeshSection { VERTEX, INDEX, TEXTURE, NONE };
Mesh3D *meshFromFile(const char *filepath) {
  std::ifstream file(filepath);
  if (!file) {
    std::cerr << "Unable to open " << filepath << "\n";
    exit(EXIT_FAILURE);
  }
  std::string line;
  MeshSection section = NONE;
  std::string tex;
  std::vector<GLfloat> vData;
  std::vector<GLuint> iData;
  while (std::getline(file, line)) {
    if (line == "[VERTEX]") {
      section = VERTEX;
      continue;
    } else if (line == "[INDEX]") {
      section = INDEX;
      continue;
    } else if (line == "[TEXTURE]") {
      section = TEXTURE;
      continue;
    }

    std::stringstream ss(line);
    std::string num;
    if (section == VERTEX) {
      while (std::getline(ss, num, ','))
        vData.push_back(std::stof(num));
    } else if (section == INDEX) {
      while (std::getline(ss, num, ','))
        iData.push_back(std::stoi(num));
    } else if (section == TEXTURE)
      tex = line;
  }
  return new Mesh3D{vData, iData, tex.c_str()};
}

Mesh3D *rimFromMesh(std::vector<GLfloat> *vData, glm::vec3 normal,
                    float thickness, const char *tex) {
  unsigned int sides =
      vData->size() / 5 - 1; // Assuming last point = first point
  std::vector<GLfloat> vxData;
  std::vector<GLuint> ixData;
  std::vector<float> cumulative(sides + 1, 0.0f);
  glm::vec3 pnt1, pnt2, pnt3, pnt4;
  float totallength = 0.0f;
  // distance data
  for (unsigned int i = 0; i < sides; i++) {
    pnt1 = glm::vec3((*vData)[i * 5], (*vData)[i * 5 + 1], (*vData)[i * 5 + 2]);
    pnt2 = (i == sides - 1)
               ? glm::vec3((*vData)[0], (*vData)[1], (*vData)[2])
               : glm::vec3((*vData)[i * 5 + 5], (*vData)[i * 5 + 1 + 5],
                           (*vData)[i * 5 + 2 + 5]);
    totallength += glm::length(pnt2 - pnt1);
    cumulative[i + 1] = totallength;
  }

  float u1, u2;
  for (unsigned int i = 0; i < sides; i++) {
    u1 = cumulative[i] / totallength;
    u2 = cumulative[i + 1] / totallength;
    pnt1 = glm::vec3((*vData)[i * 5], (*vData)[i * 5 + 1], (*vData)[i * 5 + 2]);
    pnt2 = (i == sides - 1)
               ? glm::vec3((*vData)[0], (*vData)[1], (*vData)[2])
               : glm::vec3((*vData)[i * 5 + 5], (*vData)[i * 5 + 1 + 5],
                           (*vData)[i * 5 + 2 + 5]);
    pnt3 = pnt1 + normal * thickness;
    pnt4 = pnt2 + normal * thickness;
    vxData.insert(vxData.end(),
                  {pnt1.x, pnt1.y, pnt1.z, u1,     0.0f,   pnt3.x, pnt3.y,
                   pnt3.z, u1,     1.0f,   pnt2.x, pnt2.y, pnt2.z, u2,
                   0.0f,   pnt4.x, pnt4.y, pnt4.z, u2,     1.0f});
    ixData.insert(ixData.end(), {i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 1,
                                 i * 4 + 2, i * 4 + 3});
  }
  return new Mesh3D(vxData, ixData, tex);
}

Model *car() {
  Mesh3D *wheelside11 = regularPolyFace(
      10, glm::vec3(-1.15f, -0.27f, -0.77f), glm::vec3(-0.9f, -0.27f, -0.77f),
      glm::vec3(0.0f, 0.0f, -1.0f),
      "/Users/zain/openGL/textures/wheel-side.png");

  Mesh3D *wheelside12 = regularPolyFace(
      10, glm::vec3(-1.15f, -0.27f, -0.63f), glm::vec3(-0.9f, -0.27f, -0.63f),
      glm::vec3(0.0f, 0.0f, -1.0f),
      "/Users/zain/openGL/textures/wheel-side.png");

  Mesh3D *wheelrim1 = regularPolyRim(
      10, 0.14f, glm::vec3(-1.15f, -0.27f, -0.77f),
      glm::vec3(-0.9f, -0.27f, -0.77f), glm::vec3(0.0f, 0.0f, 1.0f),
      "/Users/zain/openGL/textures/wheel-top.png");

  Mesh3D *wheelside21 = regularPolyFace(
      10, glm::vec3(1.04f, -0.27f, -0.77f), glm::vec3(1.29f, -0.27f, -0.77f),
      glm::vec3(0.0f, 0.0f, -1.0f),
      "/Users/zain/openGL/textures/wheel-side.png");

  Mesh3D *wheelside22 = regularPolyFace(
      10, glm::vec3(1.04f, -0.27f, -0.63f), glm::vec3(1.29f, -0.27f, -0.63f),
      glm::vec3(0.0f, 0.0f, -1.0f),
      "/Users/zain/openGL/textures/wheel-side.png");

  Mesh3D *wheelrim2 = regularPolyRim(
      10, 0.14f, glm::vec3(1.05f, -0.27f, -0.77f),
      glm::vec3(1.29f, -0.27f, -0.77f), glm::vec3(0.0f, 0.0f, 1.0f),
      "/Users/zain/openGL/textures/wheel-top.png");

  Mesh3D *car_side1 = meshFromFile("/Users/zain/openGL/meshes/car-side1.txt");

  Mesh3D *wheelside31 = regularPolyFace(
      10, glm::vec3(1.04f, -0.27f, 0.77f), glm::vec3(1.29f, -0.27f, 0.77f),
      glm::vec3(0.0f, 0.0f, -1.0f),
      "/Users/zain/openGL/textures/wheel-side.png");

  Mesh3D *wheelside32 = regularPolyFace(
      10, glm::vec3(1.04f, -0.27f, 0.63f), glm::vec3(1.29f, -0.27f, 0.63f),
      glm::vec3(0.0f, 0.0f, -1.0f),
      "/Users/zain/openGL/textures/wheel-side.png");

  Mesh3D *wheelrim3 = regularPolyRim(
      10, 0.14f, glm::vec3(1.05f, -0.27f, 0.77f),
      glm::vec3(1.29f, -0.27f, 0.77f), glm::vec3(0.0f, 0.0f, -1.0f),
      "/Users/zain/openGL/textures/wheel-top.png");

  Mesh3D *wheelside41 = regularPolyFace(
      10, glm::vec3(-1.15f, -0.27f, 0.77f), glm::vec3(-0.9f, -0.27f, 0.77f),
      glm::vec3(0.0f, 0.0f, -1.0f),
      "/Users/zain/openGL/textures/wheel-side.png");

  Mesh3D *wheelside42 = regularPolyFace(
      10, glm::vec3(-1.15f, -0.27f, 0.63f), glm::vec3(-0.9f, -0.27f, 0.63f),
      glm::vec3(0.0f, 0.0f, -1.0f),
      "/Users/zain/openGL/textures/wheel-side.png");

  Mesh3D *wheelrim4 = regularPolyRim(
      10, 0.14f, glm::vec3(-1.15f, -0.27f, 0.77f),
      glm::vec3(-0.9f, -0.27f, 0.77f), glm::vec3(0.0f, 0.0f, -1.0f),
      "/Users/zain/openGL/textures/wheel-top.png");

  Mesh3D *car_side2 = meshFromFile("/Users/zain/openGL/meshes/car-side2.txt");

  Mesh3D *car_rim =
      rimFromMesh(car_side1->getVdata(), glm::vec3(0.0f, 0.0f, 1.0f), 1.4,
                  "/Users/zain/openGL/textures/car-rim.png");

  Model *model = new Model();
  model->addMesh(wheelside11);
  model->addMesh(wheelside12);
  model->addMesh(wheelrim1);
  model->addMesh(wheelside21);
  model->addMesh(wheelside22);
  model->addMesh(wheelrim2);
  model->addMesh(car_side1);
  model->addMesh(wheelside31);
  model->addMesh(wheelside32);
  model->addMesh(wheelrim3);
  model->addMesh(wheelside41);
  model->addMesh(wheelside42);
  model->addMesh(wheelrim4);
  model->addMesh(car_side2);
  model->addMesh(car_rim);
  return model;
}
