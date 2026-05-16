#include "game.hpp"
void Game::Render() {
  glViewport(0, 0, screenwidth, screenheight);
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (auto mesh : meshes) {
    mesh->draw(graphicsPipeline, camera);
  }

  SDL_GL_SwapWindow(window);
}
