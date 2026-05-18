#include "map.hpp"
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
Map::Map(std::map<std::pair<int, int>, char> &map, const char *atlasTexture,
         std::map<char, struct Tile> &tileInfo, float groundy) {
  std::vector<GLfloat> vData;
  std::vector<GLuint> iData;
  float x0, x1, z0, z1;
  Tile tileI; glm::vec2 tileuvMin, tileuvMax;
  unsigned int i = 0;
  for (auto &[coord, tile] : map) {
    x0 = coord.first - 0.5f;
    x1 = coord.first + 0.5f;
    z0 = coord.second - 0.5f;
    z1 = coord.second + 0.5f;
    tileI = tileInfo[tile];
    std::cout <<tile;
    tileuvMin = tileI.uvMin;
    tileuvMax = tileI.uvMax;
    vData.insert(vData.end(), {
      x0, groundy, z0, tileuvMin.x, tileuvMin.y,
      x0, groundy, z1, tileuvMin.x, tileuvMax.y,
      x1, groundy, z1, tileuvMax.x, tileuvMax.y,
      x1, groundy, z0, tileuvMax.x, tileuvMin.y
      });
    iData.insert(iData.end(), {
      4*i, 4*i+1, 4*i+2,
      4*i, 4*i+3, 4*i+2
      });
    i++;
  }
  mesh = new Mesh3D(vData, iData, atlasTexture);
}
Mesh3D *Map::getMesh(){ return mesh; }

enum MapSection {
  NONE,
  MAPDATA,
  TILEINFO,
  ATLASDIM,
  ATLASFILE,
};

Map::Map(const char* filepath, float groundy){
  std::ifstream file(filepath);
  if(file.fail()){
    std::cerr<<"file "<<filepath<<" not found\n";
    exit(EXIT_FAILURE);
  }
  MapSection curr_section = NONE;
  size_t row = 0, col = 0;
  int texW=0, texH=0;

  std::map<std::pair<int, int>, char> map;
  std::string atlasTexture = "";
  std::map<char, struct Tile> tileInfo;
  std::string line;
  while (std::getline(file, line)) {
    if(line == "[MAPDATA]"){
      curr_section = MAPDATA;
      continue;
    } else if(line == "[TILEINFO]"){
      curr_section = TILEINFO;
      continue;
    } else if(line == "[ATLASDIM]"){
      curr_section = ATLASDIM;
      continue;
    }else if(line == "[ATLASFILE]"){
      curr_section = ATLASFILE;
      continue;
    }
 
    if(curr_section == MAPDATA){
      col = 0;
      for(char c : line){
        if(c == ' ') continue;
        map[std::make_pair(row, col)] = c;
        col++;
      }
      row++;
      continue;
    } else if(curr_section == TILEINFO){
      if(texH == 0 || texW == 0){
        printf("Incorrect formatting, declare atlas dimension before tileInfo\n");
        exit(EXIT_FAILURE);
      }
      size_t count = 0; std::string tmp = "";
      char tname; size_t x, y;
      for(char c : line){
        if(c == ' '){
          if(count == 0) tname = tmp[0];
          else if(count == 1) x = atoi(tmp.c_str());
          else if(count == 2) y = atoi(tmp.c_str());
          count++;
          tmp="";
          if(count > 2) break;
          continue;
        }
        tmp += c;
      }
      if(tmp != "") y = atoi(tmp.c_str());
      tileInfo[tname] = {glm::vec2((float)x/(float)texW, (float)y/(float)texH), 
      glm::vec2( (float)(x+1)/(float)texW , (float)(y+1)/(float)texH )};
      continue;
    } else if(curr_section == ATLASDIM){
      std::string tmp; size_t count = 0;
      for(char c: line){
        if(c == ' '){
          if(count == 0) texW = atoi(tmp.c_str());
          else if(count == 1) texH = atoi(tmp.c_str());
          count++;
          tmp = "";
          if(count > 1) break;
          continue;
        }
        tmp += c;
      }
      if(tmp!="") texH = atoi(tmp.c_str());
      continue;
    } else if(curr_section == ATLASFILE){
      atlasTexture = line;
      continue;
    }
  }
  *this = Map(map, atlasTexture.c_str(), tileInfo, groundy);
}
