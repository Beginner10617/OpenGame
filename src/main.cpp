#include "game.hpp"
#include <iostream>
int main() {
  Game game(1280, 720, "Game");
  while (game.getIsRunning()) {
    game.HandleInput();
  }
}
