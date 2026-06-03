#pragma once
#include "piece.hpp"
#include "board.hpp"
#include <SFML/Graphics.hpp>
#include <string.h>

struct Game {
    piece* board[8][8];
    int selectedRow;
    int selectedColumn;
    bool isSelected;
    
    Game();

    void userClick(int row, int col);

    void draw(sf::RenderWindow& window);

    bool performMoveValidation(int startRow, int startCol, int finalRow, int finalCol);

    void pawnPromotion(int row, int col);
};