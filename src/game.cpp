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
}

void Game::CreateGraphicsPipeline(const char *vShader, const char *fShader) {
  std::string vertexSource = LoadShaderSource(vShader);
  std::string fragmentSource = LoadShaderSource(fShader);

  const char *v = vertexSource.c_str();
  const char *f = fragmentSource.c_str();
  graphicsPipeline = CreateShaderProgram(v, f);
}

void Game::HandleInput(float deltatime) {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT)
      isRunning = false;
  }
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  float deltaX = 1.0f * deltatime, deltaA = 10.0f * deltatime;
  if (keystate[SDL_SCANCODE_W])
    camera.MoveForward(deltaX);
  if (keystate[SDL_SCANCODE_S])
    camera.MoveBackward(deltaX);
  if (keystate[SDL_SCANCODE_A])
    camera.MoveLeft(deltaX);
  if (keystate[SDL_SCANCODE_D])
    camera.MoveRight(deltaX);
  if (keystate[SDL_SCANCODE_Q])
    camera.MoveUp(deltaX);
  if (keystate[SDL_SCANCODE_E])
    camera.MoveDown(deltaX);
  if (keystate[SDL_SCANCODE_I] || keystate[SDL_SCANCODE_UP])
    camera.TurnUp(deltaA);
  if (keystate[SDL_SCANCODE_K] || keystate[SDL_SCANCODE_DOWN])
    camera.TurnDown(deltaA);
  if (keystate[SDL_SCANCODE_J] || keystate[SDL_SCANCODE_LEFT])
    camera.TurnLeft(deltaA);
  if (keystate[SDL_SCANCODE_L] || keystate[SDL_SCANCODE_RIGHT])
    camera.TurnRight(deltaA);
  if (keystate[SDL_SCANCODE_U])
    camera.TwistLeft(deltaA);
  if (keystate[SDL_SCANCODE_O])
    camera.TwistRight(deltaA);
}

Game::~Game() {
  isRunning = false;
  glDeleteProgram(graphicsPipeline);
  SDL_GL_DeleteContext(openGLContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

bool Game::getIsRunning() { return isRunning; }
void Game::addMesh(Mesh3D *mesh) { meshes.push_back(mesh); }
void Game::clearMeshes() { meshes.clear(); }
void Game::addModel(Model *model) {
  size_t sz = model->size();
  for (size_t i = 0; i < sz; i++) {
    addMesh(model->meshAt(i));
  }
}

// helprer functions
void Game::Render() {
  glViewport(0, 0, screenwidth, screenheight);
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (auto mesh : meshes) {
    mesh->draw(graphicsPipeline, camera);
  }

  SDL_GL_SwapWindow(window);
}
