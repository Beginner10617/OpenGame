#ifndef MAP_HPP
#define MAP_HPP
#include "mesh.hpp"
#include <map>
#include <utility>
struct Tile {
  glm::vec2 uvMin;
  glm::vec2 uvMax;
};
class Map {
public:
  Map(std::map<std::pair<int, int>, char> &map, const char *atlasTexture,
      std::map<char, struct Tile> &tileInfo, float groundy = 0.0f,
      float scale = 1.0f);
  Mesh3D *getMesh();
  Map(const char *file, float groundy = 0.0f, float scale = 1.0f);

  std::map<std::pair<int, int>, char> data;

private:
  Mesh3D *mesh;
};

#endif
