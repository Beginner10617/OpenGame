#include "model.hpp"
void Model::addMesh(Mesh3D *mesh) { meshes.push_back(mesh); }
void Model::applyTranslation(glm::vec3 tran) {
  for (auto mesh : meshes) {
    mesh->applyTranslation(tran);
  }
}
void Model::applyRotn(glm::vec3 eulerAngle) {
  for (auto mesh : meshes) {
    mesh->applyRotation(eulerAngle);
  }
}
void Model::applyScale(glm::vec3 scale) {
  for (auto mesh : meshes) {
    mesh->applyScale(scale);
  }
}
void Model::reset(){
  for(auto mesh: meshes)
    mesh->reset();
}
void Model::draw(GLuint pipeline, const Camera &camera) {
  for (auto mesh : meshes) {
    mesh->draw(pipeline, camera);
  }
}
size_t Model::size() { return meshes.size(); }
Mesh3D *Model::meshAt(size_t index) {
  if (index >= meshes.size())
    return NULL;
  return meshes[index];
}
void Model::addModel(Model *model){
  size_t n = model->size();
  for(size_t i=0; i<n; i++){
    addMesh(meshAt(i));
  }
}
