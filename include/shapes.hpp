#ifndef SHAPES_HPP
#define SHAPES_HPP
#include "mesh.hpp"
#include "model.hpp"
// helper functions
Mesh3D *regularPolyFace(unsigned int sides, glm::vec3 origin, glm::vec3 vertex0,
                        glm::vec3 normal, const char *tex);
Mesh3D *regularPolyRim(unsigned int sides, float thickness, glm::vec3 origin,
                       glm::vec3 vertex0, glm::vec3 normal, const char *tex);
Mesh3D *meshFromFile(const char *filepath);
Mesh3D *rimFromMesh(std::vector<GLfloat> *vData, glm::vec3 normal,
                    float thickness, const char *texture);

// special shapes
Model *car();
Mesh3D *ground(float yCoord, int x, int y, int width, int height,
              const char *tex);
#endif
