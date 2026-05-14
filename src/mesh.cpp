#include <cstdlib>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "mesh.hpp"
#include "stb_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
void Mesh3D::updateTransform(const Transform &trnsfrm) { transform = trnsfrm; }
Transform Mesh3D::getTransform() { return transform; }
void Mesh3D::applyRotation(glm::vec3 eulerAngles) {
  transform.EulerAngles += eulerAngles;
}
void Mesh3D::applyTranslation(glm::vec3 translate) {
  transform.Translate += translate;
}
void Mesh3D::applyScale(glm::vec3 scale) { transform.Scale = scale; }
std::vector<GLfloat> *Mesh3D::getVdata() { return &vertexData; }

Mesh3D::Mesh3D(const std::vector<GLfloat> &vxData,
               const std::vector<GLuint> &ixData, const char *texturePath) {

  vertexData = vxData;
  indexData = ixData;
  int width, height, nrChannels;

  stbi_set_flip_vertically_on_load(true);

  unsigned char *texData =
      stbi_load(texturePath, &width, &height, &nrChannels, 0);
  if (!texData) {
    std::cout << "Failed to load texture\n";
    std::cout << "path: " << texturePath << "\n";
    exit(EXIT_FAILURE);
  }

  GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

  // Texture
  glGenTextures(1, &textureObj);
  glBindTexture(GL_TEXTURE_2D, textureObj);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
               GL_UNSIGNED_BYTE, texData);

  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(texData);

  // VAO
  glGenVertexArrays(1, &vertexArrayObj);
  glBindVertexArray(vertexArrayObj);

  // VBO
  glGenBuffers(1, &vertexBufferObj);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);

  glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat),
               vertexData.data(), GL_STATIC_DRAW);

  // EBO
  glGenBuffers(1, &indexBufferObj);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObj);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint),
               indexData.data(), GL_STATIC_DRAW);

  // Position
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5,
                        (void *)0);

  // Texture coords
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5,
                        (void *)(sizeof(GLfloat) * 3));

  glBindVertexArray(0);
}

void Mesh3D::draw(GLuint pipeline, const Camera &camera) {

  glUseProgram(pipeline);
  GLint u_ModelMatlocn = glGetUniformLocation(pipeline, "u_ModelMatrix");
  if (u_ModelMatlocn < 0) {
    std::cerr << "Can't find \"u_ModelMatrix\" maybe spelling error\n";
    exit(EXIT_FAILURE);
  }
  GLint u_projectionlocn = glGetUniformLocation(pipeline, "u_Projection");
  if (u_projectionlocn < 0) {
    std::cerr << "Can't find \"u_Projection\" maybe spelling error\n";
    exit(EXIT_FAILURE);
  }
  GLint u_viewlocn = glGetUniformLocation(pipeline, "u_ViewMatrix");
  if (u_viewlocn < 0) {
    std::cerr << "Can't find \"u_ViewMatrix\" maybe spelling error\n";
    exit(EXIT_FAILURE);
  }
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, transform.Translate);
  // std::cout<<"Translate: "<<transform.Translate.x<<", "
  //   <<transform.Translate.y<<", "<<transform.Translate.z<<"\n";
  model = glm::rotate(model, glm::radians(transform.EulerAngles.x),
                      glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, glm::radians(transform.EulerAngles.y),
                      glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, glm::radians(transform.EulerAngles.z),
                      glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, transform.Scale);

  glm::mat4 projection = camera.getProjection();
  glm::mat4 view = camera.getViewMatrix();
  glUniformMatrix4fv(u_ModelMatlocn, 1, GL_FALSE, &model[0][0]);
  glUniformMatrix4fv(u_projectionlocn, 1, GL_FALSE, &projection[0][0]);
  glUniformMatrix4fv(u_viewlocn, 1, GL_FALSE, &view[0][0]);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureObj);
  glBindVertexArray(vertexArrayObj);
  glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, 0);
  glUseProgram(0);
}
