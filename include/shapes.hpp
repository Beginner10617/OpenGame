#ifndef SHAPES_HPP
#define SHAPES_HPP
#include "game.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "physics.hpp"
// helper functions
Mesh3D *regularPolyFace(unsigned int sides, glm::vec3 origin, glm::vec3 vertex0,
                        glm::vec3 normal, const char *tex);
Mesh3D *regularPolyRim(unsigned int sides, float thickness, glm::vec3 origin,
                       glm::vec3 vertex0, glm::vec3 normal, const char *tex);
Mesh3D *meshFromFile(const char *filepath);
Mesh3D *rimFromMesh(std::vector<GLfloat> *vData, glm::vec3 normal,
                    float thickness, const char *texture);

// special shapes
class Car {
public:
  Car(glm::vec3 spawnPoint, glm::vec2 direction, Game &game);
  void preDraw();
  Rigidbody rigidbody{10.0f, 10.0f};

private:
  Model *carBody;
  Model *wheels[4];
};
Mesh3D *ground(float yCoord, int x, int y, int width, int height,
               const char *tex);
#endif
