// Copyright 2014 hellovai

#include <gflags/gflags.h>
#include <iostream>
#include "game.h"

// DEFINE_int32(boardsize, 9, "modify boardsize of the game");

int State::boardSize = 19;
int Move::maxMoveSize = State::boardSize - 1;

int main() {
  Game* game = new Game();
  while (!game->isFinished()) {
    game->print();
    Move *move = new Move();
    char x;
    int y;
    std::cout << "Move: ";
    std::cin >> x;
    if (x != 'p' && x != 'P') {
      std::cin >> y;
      move->y = static_cast<int>(x) - 0x41;
      move->x = y - 1;
      move->pass = false;
      move->setIndex();
    }
    game->makeMove(move);
    std::cout << "MOVE: " << *move << std::endl;
  }
  return 0;
}