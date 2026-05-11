#define GLM_FORCE_SWIZZLE
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/geometric.hpp"
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include "glm/mat4x4.hpp" //glm::mat4
#include "glm/vec3.hpp"
#include "glm/vec4.hpp" // glm: :vec4
#include <iostream>

int main() {
  glm::vec3 C(1.0f);
  glm::vec3 B(0.5f, 1.0f, 0.0f);
  glm::vec3 A = glm::normalize(C);
  A.xyz() = B.zxy();
  float f = glm::dot(A, B);
  std::cout << glm::to_string(A) << " * " << glm::to_string(B) << " = " << f
            << "\n";
  return 0;
}
