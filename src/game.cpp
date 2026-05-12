#include "game.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
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
  isRunning = true;
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

void Game::CreateGraphicsPipeline(const char *vShader, const char *fShader) {
  std::string vertexSource = LoadShaderSource(vShader);
  std::string fragmentSource = LoadShaderSource(fShader);

  const char *v = vertexSource.c_str();
  const char *f = fragmentSource.c_str();
  graphicsPipeline = CreateShaderProgram(v, f);
}

void Game::HandleInput() {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT)
      isRunning = false;
  }
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

// helprer functions
void drawMesh(Mesh3D *mesh, GLuint pipeline, const Camera &camera) {

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
  glm::mat4 view = camera.getViewMatrix();
  GLint u_viewlocn = glGetUniformLocation(pipeline, "u_ViewMatrix");
  if (u_viewlocn < 0) {
    std::cerr << "Can't find \"u_ViewMatrix\" maybe spelling error\n";
    exit(EXIT_FAILURE);
  }
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, mesh->getTransform().Translate);
  // model = glm::rotate(model, (mesh->m_uangle), glm::vec3(0.0f, 1.0f, 0.0f));
  // model = glm::scale(model,
  //                    glm::vec3(mesh->m_uscale, mesh->m_uscale,
  //                    mesh->m_uscale));
  glm::mat4 projection = camera.getProjection();
  glUniformMatrix4fv(u_ModelMatlocn, 1, false, &model[0][0]);
  glUniformMatrix4fv(u_projectionlocn, 1, false, &projection[0][0]);
  glUniformMatrix4fv(u_viewlocn, 1, false, &view[0][0]);
  glUseProgram(pipeline);
  glBindVertexArray(mesh->vertexArrayObj);
  glDrawElements(GL_TRIANGLES, mesh->indexData.size(), GL_UNSIGNED_INT, 0);
  glUseProgram(0);
}
void Game::Render() {
  for (auto mesh : meshes) {
    drawMesh(mesh, graphicsPipeline, camera);
  }

  SDL_GL_SwapWindow(window);
}
