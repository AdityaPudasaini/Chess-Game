#include "Game.hpp"

Game::Game() {
    
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            board[row][col] = nullptr;
        }
    }

    selectedRow = -1;
    selectedColumn = -1;
    isSelected = false;

    board[0][0] = new piece(pieceType::rook, pieceColor::black);
    board[0][1] = new piece(pieceType::knight, pieceColor::black);
    board[0][2] = new piece(pieceType::bishop, pieceColor::black);
    board[0][3] = new piece(pieceType::king, pieceColor::black);
    board[0][4] = new piece(pieceType::queen, pieceColor::black);
    board[0][5] = new piece(pieceType::bishop, pieceColor::black);
    board[0][6] = new piece(pieceType::knight, pieceColor::black);
    board[0][7] = new piece(pieceType::rook, pieceColor::black);

    for(int col = 0; col < 8; col++) {
        board[1][col] = new piece(pieceType::pawn, pieceColor::black);
    }

    board[7][0] = new piece(pieceType::rook, pieceColor::white);
    board[7][1] = new piece(pieceType::knight, pieceColor::white);
    board[7][2] = new piece(pieceType::bishop, pieceColor::white);
    board[7][3] = new piece(pieceType::king, pieceColor::white);
    board[7][4] = new piece(pieceType::queen, pieceColor::white);
    board[7][5] = new piece(pieceType::bishop, pieceColor::white);
    board[7][6] = new piece(pieceType::knight, pieceColor::white);
    board[7][7] = new piece(pieceType::rook, pieceColor::white);

    for(int col = 0; col < 8; col++) {
        board[6][col] = new piece(pieceType::pawn, pieceColor::white);
    }
}

void Game::userClick(int row, int column) {

    if(promotion) {
        return;
    }

    if(row == selectedRow && column == selectedColumn) {
        isSelected = false;
        selectedColumn = -1;
        selectedRow = -1;
    }

    else if(!isSelected) {
        if((board[row][column]) != nullptr) {
            selectedRow = row;
            selectedColumn = column;
            isSelected = true;
        }
    }

    else {
        if(performMoveValidation(selectedRow, selectedColumn, row, column)) {
            board[row][column] = board[selectedRow][selectedColumn];
            board[selectedRow][selectedColumn] = nullptr;
            pawnPromotion(row, column);
            isSelected = false;
            selectedColumn = -1;
            selectedRow = -1;
        }
    }
}

void Game::draw(sf::RenderWindow& window) {
    drawBoard(window);

    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            if(board[row][col] != nullptr) {
                board[row][col]->draw(window, row, col);
            }
        }    
    }

    if(promotion) {
        piece* forPromotion[4];
        forPromotion[0] = new piece(pieceType::queen, color);
        forPromotion[1] = new piece(pieceType::rook, color);
        forPromotion[2] = new piece(pieceType::knight, color); 
        forPromotion[3] = new piece(pieceType::bishop, color);

        int startCol = (promotionCol <= 3) ? 0 : 4;

        sf::RectangleShape promotionRectangle;
        promotionRectangle.setSize(sf::Vector2f(100, 100));
        promotionRectangle.setFillColor(sf::Color(148, 148, 148));

        if(promotionCol == 0) {
            if(color == pieceColor::white) {
                for(int i = 0; i < 4; i++) {
                    promotionRectangle.setPosition({(startCol + i) * 100, promotionRow * 100});
                    window.draw(promotionRectangle);    
                    forPromotion[i]->draw(window, promotionRow, startCol + i);
                }
            }
        }
    }
}

bool Game::performMoveValidation(int startRow, int startCol, int finalRow, int finalCol) {
    piece* p = board[startRow][startCol];

    if(p->type == pieceType::pawn) {
        int direction = (p->color == pieceColor::white) ? -1 : 1;
        int rowDifference = finalRow - startRow;
        int colDifference = finalCol - startCol;

        //First rule - Moving 1 place or 2 place
        if(startCol == finalCol && board[finalRow][finalCol] == nullptr) {

            if((startRow == 1 || startRow == 6) && (rowDifference == 2 * direction)) {
                finalRow = startRow + 2 * direction;
                return true;
            }

            if(rowDifference == 1 || rowDifference == -1) {
                finalRow = startRow + direction;
                return true;
            }
        }

        // Second rule - Can only capture sideways
        if(startCol != finalCol && board[finalRow][finalCol] != nullptr) {

            if(rowDifference == 1 || rowDifference == -1) {

                if(colDifference == 1 || colDifference == -1) {

                    finalRow = startRow + direction;
                    finalCol = startCol + colDifference;

                    return true;
                }
            }
        }
    }

    return false;
}

void Game::pawnPromotion(int row, int col) {
    piece* p = board[row][col];
    
    if(p->type == pieceType::pawn) {
        if(p->color == pieceColor::white && row == 0) {
            promotionRow = row;
            promotionCol = col;
            color = p->color;
            promotion = true;
        }

        if(p->color == pieceColor::black && row == 7) {
            promotionRow = row;
            promotionCol = col;
            color = p->color;
            promotion = true;
        }
    }
}

void Game::handlePromotionClick(int x, int y) {
    int clickedRow = y / 100;
    int clickedCol = x / 100;

    int startCol = (promotionCol <= 3) ? 0 : 4;

    if(clickedRow == promotionRow) {
        if (clickedCol >= startCol && clickedCol <= startCol + 3) {
            int choice = clickedCol - startCol;

            switch (choice)
            {
                case 0:
                    delete board[promotionRow][promotionCol];
                    board[promotionRow][promotionCol] = new piece(pieceType::queen, color);
                    break;
                
                case 1:
                    delete board[promotionRow][promotionCol];
                    board[promotionRow][promotionCol] = new piece(pieceType::bishop, color);
                    break;
                
                case 2:
                    delete board[promotionRow][promotionCol];
                    board[promotionRow][promotionCol] = new piece(pieceType::knight, color);
                    break;

                case 3:
                    delete board[promotionRow][promotionCol];
                    board[promotionRow][promotionCol] = new piece(pieceType::rook, color);
                    break;
            }

            promotion = false;
        }
    }
}