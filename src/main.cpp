#include "game.hpp"
int main() {
  Game game(50, 50, "Game");
  while (game.getIsRunning()) {
    game.HandleInput();
  }
}
