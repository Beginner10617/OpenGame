#include "shapes.hpp"
#include <cmath>
#define PI 3.14159265

Mesh3D *regularPolyFace(unsigned int sides, glm::vec3 origin, glm::vec3 vertex0,
    glm::vec3 normal, const char *tex){
  glm::vec3 x = glm::normalize(vertex0 - origin);
  glm::vec3 y = glm::normalize( glm::cross(x, normal) );
  float radius= glm::length(vertex0 - origin);
  std::vector<GLfloat> vData{origin.x, origin.y, origin.z, 0.5f, 0.5f};
  std::vector<GLuint> iData;
  glm::vec3 pnt; float u, v;
  for(unsigned int i=0; i<sides; i++){
    pnt = origin 
      + (float) std::cos((float)2*PI*i / (float)sides) * radius * x 
      + (float) std::sin((float)2*PI*i / (float)sides) * radius * y;
    u = 0.5f + (float) std::cos((float)2*PI*i / (float)sides) * 0.5f;
    v = 0.5f + (float) std::sin((float)2*PI*i / (float)sides) * 0.5f;
    vData.insert(vData.end(),{pnt.x, pnt.y, pnt.z, u, v});
    iData.insert(iData.end(),{0, i+1, (i+2>sides ? 1 : i+2) });
  }
  return new Mesh3D{vData, iData, tex};
}
Mesh3D *regularPolyRim(unsigned int sides, float thickness, glm::vec3 origin, 
    glm::vec3 vertex0, glm::vec3 normal, const char *tex){
  glm::vec3 x = glm::normalize(vertex0 - origin);
  glm::vec3 y = glm::normalize( glm::cross(x, normal) );
  float radius= glm::length(vertex0 - origin);
  std::vector<GLfloat> vData;
  std::vector<GLuint> iData;
  glm::vec3 pnt1, pnt2; float u;
 
  for(unsigned int i=0; i<sides; i++){
    pnt1 = origin 
      + (float) std::cos((float)2*PI*i / (float)sides) * radius * x 
      + (float) std::sin((float)2*PI*i / (float)sides) * radius * y;
    pnt2 = pnt1 + normal * thickness;
    u = (float) i / (float) sides;
    vData.insert(vData.end(),{
        pnt1.x, pnt1.y, pnt1.z, u, 0.0f,
        pnt2.x, pnt2.y, pnt2.z, u, 1.0f});
    iData.insert(iData.end(),{2*i, 2*i+1, 2*i+2, 2*i+1, 2*i+3, 2*i+2});
  }
  pnt1 = origin + radius * x;
  pnt2 = pnt1 + normal * thickness;
  vData.insert(vData.end(),{
      pnt1.x, pnt1.y, pnt1.z, 1.0f, 0.0f,
      pnt2.x, pnt2.y, pnt2.z, 1.0f, 1.0f
      });
  return new Mesh3D{vData, iData, tex};
}
