#pragma once
#include "piece.hpp"
#include "board.hpp"
#include <SFML/Graphics.hpp>

struct Game {
    piece* board[8][8];
    int selectedRow;
    int selectedColumn;
    bool isSelected;

    Game();

    void userClick(int row, int col);

    void draw(sf::RenderWindow& window);
};