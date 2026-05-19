#include "game.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
// helper functions
void GetOpenGLContextInfo() {
  std::cout << "Vendor:       " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer:     " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Version:      " << glGetString(GL_VERSION) << std::endl;
  std::cout << "Shading Lang: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;
}
std::string LoadShaderSource(const char *filepath) {
  std::ifstream file(filepath);

  if (!file.is_open()) {
    std::cerr << "Failed to open shader file\n";
    exit(EXIT_FAILURE);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  return buffer.str();
}

GLuint CompileShader(GLuint type, const char *source) {
  GLuint shaderObj;
  switch (type) {

  case GL_VERTEX_SHADER:
    shaderObj = glCreateShader(GL_VERTEX_SHADER);
    break;
  case GL_FRAGMENT_SHADER:
    shaderObj = glCreateShader(GL_FRAGMENT_SHADER);
    break;
  default:
    std::cout << "Invalid type\n";
    exit(EXIT_FAILURE);
  }
  glShaderSource(shaderObj, 1, &source, nullptr);
  glCompileShader(shaderObj);

  // Check compile status
  GLint success;
  glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);

  if (success == GL_FALSE) {
    GLint logLength = 0;
    glGetShaderiv(shaderObj, GL_INFO_LOG_LENGTH, &logLength);

    std::vector<char> infoLog(logLength);
    glGetShaderInfoLog(shaderObj, logLength, nullptr, infoLog.data());

    std::cerr << "Shader compilation failed:\n";
    std::cerr << infoLog.data() << std::endl;

    glDeleteShader(shaderObj);
    exit(EXIT_FAILURE);
  }

  return shaderObj;
}
GLuint CreateShaderProgram(const char *vertexshadersource,
                           const char *fragmentshadersource) {

  GLuint programobject = glCreateProgram();
  GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER, vertexshadersource);
  GLuint myFragmentShader =
      CompileShader(GL_FRAGMENT_SHADER, fragmentshadersource);
  glAttachShader(programobject, myVertexShader);
  glAttachShader(programobject, myFragmentShader);
  glLinkProgram(programobject);

  glValidateProgram(programobject);
  return programobject;
}

Game::Game(int width, int height, const char *title) {
  // Init SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Error initializing SDL\n";
    exit(EXIT_FAILURE);
  }

  // Setting up OpenGL Context Attributes
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); // Version 4.1

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  // Window setup
  screenwidth = width;
  screenheight = height;
  window = SDL_CreateWindow(title, 50, 50, screenwidth, screenheight,
                            SDL_WINDOW_OPENGL);
  if (window == nullptr) {
    printf("Error creating window\n");
    exit(EXIT_FAILURE);
  }

  // Creating OpenGL Context
  openGLContext = SDL_GL_CreateContext(window);
  if (openGLContext == nullptr) {
    printf("Error creating openGL context\n");
    exit(EXIT_FAILURE);
  }

  // Initialize the GLAD Library
  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
    printf("Error loading GLAD Library\n");
    exit(EXIT_FAILURE);
  }
  GetOpenGLContextInfo();

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  isRunning = true;

  // adding player
  Car *car = new Car(glm::vec3(5.0f, 0.0f, 5.5f), glm::vec2(0.0f, -1.0f));
  this->addModel(car->carBody);
  for (int i = 0; i < 4; i++)
    this->addModel(car->wheels[i]);
  player = car;
}

void Game::CreateGraphicsPipeline(const char *vShader, const char *fShader) {
  std::string vertexSource = LoadShaderSource(vShader);
  std::string fragmentSource = LoadShaderSource(fShader);

  const char *v = vertexSource.c_str();
  const char *f = fragmentSource.c_str();
  graphicsPipeline = CreateShaderProgram(v, f);
}

Game::~Game() {
  isRunning = false;
  glDeleteProgram(graphicsPipeline);
  SDL_GL_DeleteContext(openGLContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool Game::getIsRunning() { return isRunning; }
size_t Game::addMesh(Mesh3D *mesh) {
  size_t out = meshes.size();
  meshes.push_back(mesh);
  return out;
}
void Game::clearMeshes() { meshes.clear(); }
size_t Game::addModel(Model *model) {
  size_t out = meshes.size();
  size_t sz = model->size();
  for (size_t i = 0; i < sz; i++) {
    addMesh(model->meshAt(i));
  }
  return out;
}

std::pair<int, int> Game::getPlayerBlock() {
  float x = player->rigidbody.getPosition().x / mapscale,
        y = player->rigidbody.getPosition().z / mapscale;
  int X = x, Y = y;
  if (x - (float)X > 0.5f)
    X++;
  if (y - (float)Y > 0.5f)
    Y++;
  return std::make_pair(X, Y);
}
void Game::setMapData(std::map<std::pair<int, int>, char> &data, float scale) {
  mapData = data;
  mapscale = scale;
}
char Game::tileBelowPlayer() { return mapData[getPlayerBlock()]; }
