#include "game.hpp"
void Game::Render() {
  player->preDraw();
  glViewport(0, 0, screenwidth, screenheight);
  glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (auto mesh : meshes) {
    mesh->draw(graphicsPipeline, camera);
  }

  SDL_GL_SwapWindow(window);
}
