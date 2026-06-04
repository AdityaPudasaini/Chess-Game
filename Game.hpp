#pragma once
#include "piece.hpp"
#include "board.hpp"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>

struct Game {
    piece* board[8][8];
    int selectedRow, selectedColumn, promotionRow, promotionCol;
    bool isSelected;
    bool promotion = false;
    pieceColor color;

    
    Game();

    void userClick(int row, int col);

    void draw(sf::RenderWindow& window);

    bool performMoveValidation(int startRow, int startCol, int finalRow, int finalCol);

    void pawnPromotion(int row, int col);

    void handlePromotionClick(int x, int y);

    bool pieceBlockingRook(int startRow, int startCol, int finalRow, int finalCol);
};