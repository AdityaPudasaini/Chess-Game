#include "Game.hpp"

Game::Game() {
    piece* board[8][8] {nullptr};
    selectedRow = -1;
    selectedColumn = -1;
    isSelected = false;
}