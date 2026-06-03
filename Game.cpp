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
        board[row][column] = board[selectedRow][selectedColumn];
        board[selectedRow][selectedColumn] = nullptr;
        isSelected = false;
        selectedColumn = -1;
        selectedRow = -1;
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
}