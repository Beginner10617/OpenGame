#ifndef MESH_HPP
#define MESH_HPP
#include "camera.hpp"
#include "glm/glm.hpp"
#include <glad/glad.h>
#include <vector>
struct Transform {
  glm::vec3 Translate{0.0f};
  glm::vec3 EulerAngles{0.0f};
  glm::vec3 Scale{1.0f};
};
class Mesh3D {
public:
  Mesh3D(
      const std::vector<GLfloat> &vData, const std::vector<GLuint> &iData,
      const char *texture); // vertex data assumed of the form : x, y, z, u, v
  void updateTransform(const Transform &transform);
  Transform getTransform();
  void draw(GLuint pipeline, const Camera &camera);

private:
  std::vector<GLfloat> vertexData;
  GLuint vertexArrayObj, vertexBufferObj, indexBufferObj, textureObj;
  std::vector<GLuint> indexData;
  Transform transform;
};
#endif
