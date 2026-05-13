#ifndef MODEL_HPP
#define MODEL_HPP
#include "camera.hpp"
#include "mesh.hpp"
#include <vector>
class Model {
public:
  void addMesh(Mesh3D *mesh);
  void applyTranslation(glm::vec3 tran);
  void applyScale(glm::vec3 scale);
  void applyRotn(glm::vec3 rotn);
  void draw(GLuint pipeline, const Camera &camera);
  size_t size();
  Mesh3D *meshAt(size_t index);

private:
  std::vector<Mesh3D *> meshes;
};
#endif
