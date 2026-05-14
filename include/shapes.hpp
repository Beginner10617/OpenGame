#ifndef SHAPES_HPP
#define SHAPES_HPP
#include "mesh.hpp"
#include "model.hpp"
// helper functions
Mesh3D *regularPolyFace(unsigned int sides, glm::vec3 origin, glm::vec3 vertex0,
    glm::vec3 normal, const char *tex);
Mesh3D *regularPolyRim(unsigned int sides, float thickness, glm::vec3 origin, 
    glm::vec3 vertex0, glm::vec3 normal, const char *tex);
Mesh3D *meshFromFile(const char* filepath);
Mesh3D *rimFromMesh(Mesh3D *mesh);

//special shapes
Model *car();
#endif
