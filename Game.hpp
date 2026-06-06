#pragma once
#include "piece.hpp"
#include "board.hpp"
#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <cmath>

struct Game {
    piece* board[8][8];
    int selectedRow, selectedColumn, promotionRow, promotionCol, enPassantCol, enPassantRow;
    bool isSelected;
    bool promotion = false;
    pieceColor color, currentTurn, winner, enPassantColor;
    bool gameOver = false, isDraw = false, whiteKingMoved, blackKingMoved, whiteRookLeftMoved, whiteRookRightMoved, blackRookLeftMoved, blackRookRightMoved;
    piece* promotionPieces[4] = {nullptr, nullptr, nullptr, nullptr};
    
    Game();

    void userClick(int row, int col);

    void draw(sf::RenderWindow& window);

    bool performMoveValidation(int startRow, int startCol, int finalRow, int finalCol);

    void pawnPromotion(int row, int col);

    void handlePromotionClick(int x, int y);

    bool pieceBlockingStraight(int startRow, int startCol, int finalRow, int finalCol);

    bool pieceBlockingDiagonal(int startRow, int startCol, int finalRow, int finalCol);

    bool isInCheck(pieceColor color);

    bool isCheckmate(pieceColor color);

    bool isLegalMove(int startRow, int startCol, int finalRow, int finalCol);

    bool isStalemate(pieceColor color);
};