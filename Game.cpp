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
    enPassantCol = -1;
    enPassantRow = -1;
    currentTurn = pieceColor::white;
    whiteKingMoved = false;;
    blackKingMoved = false;;
    whiteRookLeftMoved = false;;
    whiteRookRightMoved = false;;
    blackRookLeftMoved = false;;
    blackRookRightMoved = false;

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

    if(promotion || gameOver) {
        return;
    }

    if(row == selectedRow && column == selectedColumn) {
        isSelected = false;
        selectedColumn = -1;
        selectedRow = -1;
    }

    else if(!isSelected) {
        if((board[row][column]) != nullptr && board[row][column]->color == currentTurn) {
            selectedRow = row;
            selectedColumn = column;
            isSelected = true;
        }
    }

    else {
        if(performMoveValidation(selectedRow, selectedColumn, row, column)) {
            piece* captured = board[row][column];
            piece* movedPiece = board[selectedRow][selectedColumn];

            int moveStartRow = selectedRow;

            board[row][column] = board[selectedRow][selectedColumn];
            board[selectedRow][selectedColumn] = nullptr;

            if(board[row][column]->type == pieceType::king && abs(column - selectedColumn) == 2) {

                if(column > selectedColumn) {
                    board[row][column - 1] = board[row][7];
                    board[row][7] = nullptr;
                } 
                
                else {
                    board[row][column + 1] = board[row][0];
                    board[row][0] = nullptr;
                }
            }

            int direction = (board[row][column]->color == pieceColor::white) ? -1 : 1;

            if(movedPiece->type == pieceType::king) {
                if(movedPiece->color == pieceColor::white) {
                    whiteKingMoved = true;
                }

                else {
                    blackKingMoved = true;
                }
            }

            if(movedPiece->type == pieceType::rook) {

                if(movedPiece->color == pieceColor::white) {

                    if(selectedColumn  == 0) {
                        whiteRookLeftMoved = true;
                    }

                    if(selectedColumn  == 7) {
                        whiteRookRightMoved = true;
                    }
                } 
                
                else {
                    if(selectedColumn  == 0) {
                        blackRookLeftMoved = true;
                    }

                    if(selectedColumn  == 7) {
                        blackRookRightMoved = true;
                    }
                }
            }

            if(board[row][column]->type == pieceType::pawn && row == enPassantRow + direction && column == enPassantCol && captured == nullptr) {
                delete board[enPassantRow][enPassantCol];
                board[enPassantRow][enPassantCol] = nullptr;
            }

            if(board[row][column]->type == pieceType::pawn && abs(row - moveStartRow) == 2) {
                enPassantRow = row;
                enPassantCol = column;
                enPassantColor = board[row][column]->color;     
            } 
            
            else {
                enPassantRow = -1;
                enPassantCol = -1;
            }

            pawnPromotion(row, column);

            if(isInCheck(currentTurn)) {
                board[selectedRow][selectedColumn] = board[row][column];
                board[row][column] = captured;
                isSelected = false;
                selectedRow = -1;
                selectedColumn = -1;
                return;
            }            

            isSelected = false;
            selectedColumn = -1;
            selectedRow = -1;

            if(!promotion) {
                currentTurn = (currentTurn == pieceColor::white) ? pieceColor::black : pieceColor::white;

                std::string hash = getBoardHash();
                positionHistory[hash]++;

                if(positionHistory[hash] >= 3) {
                    gameOver = true;
                    isDraw = true;
                }
            }

            if(isCheckmate(currentTurn)) {
                gameOver = true;
                winner = (currentTurn == pieceColor::white) ? pieceColor::black : pieceColor::white;
            }

            if(isStalemate(currentTurn)) {
                gameOver = true;
                isDraw = true;
            }
        }
    }
}

void Game::draw(sf::RenderWindow& window) {
    drawBoard(window);

    if(isSelected) {
        sf::RectangleShape selectedTile({100.f, 100.f});
        selectedTile.setFillColor(sf::Color(255, 255, 0, 100));
        selectedTile.setPosition({selectedColumn * 100.f, selectedRow * 100.f});
        window.draw(selectedTile);

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if(isLegalMove(selectedRow, selectedColumn, row, col)) {
                    sf::RectangleShape validTiles({100.f, 100.f});
                    validTiles.setFillColor(sf::Color(0, 255, 0, 100));
                    validTiles.setPosition({col * 100.f, row * 100.f});
                    window.draw(validTiles);
                }
            }
        }
    }

    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            if(board[row][col] != nullptr) {
                board[row][col]->draw(window, row, col);
            }
        }    
    }

    if(promotion) {
        int startCol = (promotionCol <= 3) ? 0 : 4;

        sf::RectangleShape promotionRectangle;
        promotionRectangle.setSize(sf::Vector2f(100, 100));
        promotionRectangle.setFillColor(sf::Color(148, 148, 148));

        for(int i = 0; i < 4; i++) {
            promotionRectangle.setPosition({(startCol + i) * 100.f, promotionRow * 100.f});
            window.draw(promotionRectangle);    
            promotionPieces[i]->draw(window, promotionRow, startCol + i);
        }
    }

    if(gameOver) {
        sf::RectangleShape winnerScreen({800.f, 800.f});
        winnerScreen.setFillColor(sf::Color(0, 0, 0, 160));
        window.draw(winnerScreen);

        sf::Font font;
        if(!font.openFromFile("./assets/font.ttf")) {
            return; 
        }

        std::string whoWon;

        if(isDraw) {
            whoWon = "Draw";
        }

        else {
            whoWon = (winner == pieceColor::white) ? "White Wins!" : "Black Wins!";
        }

        sf::Text text(font);
        text.setString(whoWon);
        text.setCharacterSize(60);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
        text.setPosition({400.f, 400.f});

        window.draw(text);
    }
}

bool Game::performMoveValidation(int startRow, int startCol, int finalRow, int finalCol) {
    piece* p = board[startRow][startCol];

    if(p->type == pieceType::pawn) {
        int direction = (p->color == pieceColor::white) ? -1 : 1;
        int rowDifference = finalRow - startRow;
        int colDifference = finalCol - startCol;

        if(board[finalRow][finalCol] != nullptr && board[finalRow][finalCol]->color == p->color) {
            return false;
        }

        //First rule - Moving 1 place or 2 place
        if(startCol == finalCol && board[finalRow][finalCol] == nullptr) {

            if((startRow == 1 || startRow == 6) && (rowDifference == 2 * direction)) {
                finalRow = startRow + 2 * direction;
                return true;
            }

            if(rowDifference == direction) {
                finalRow = startRow + direction;
                return true;
            }
        }

        // Second rule - Can only capture sideways
        if(startCol != finalCol && board[finalRow][finalCol] != nullptr) {

            if(rowDifference == direction) {

                if(colDifference == 1 || colDifference == -1) {

                    finalRow = startRow + direction;
                    finalCol = startCol + colDifference;



                    return true;
                }
            }
        }

        //Third Rule - EnPassant
        if(enPassantCol != -1 && enPassantRow != -1) {

            if(rowDifference == direction && (colDifference == 1 || colDifference == -1)) {

                if(finalRow == enPassantRow + direction && finalCol == enPassantCol && board[finalRow][finalCol] == nullptr && enPassantColor != p->color) {
                    return true;
                }
            }
        }

        return false;
    }

    else if(p->type ==  pieceType::rook) {

        // Checking if the rook is trying to move to its current position
        if(startRow == finalRow && startCol == finalCol) {
            return false;
        }

        //Checking if the rook is trying to move not straight
        else if(startRow != finalRow && startCol != finalCol) {
            return false;
        }

        else {

            //Checking if the piece is the same color as the rook
            if(board[finalRow][finalCol] != nullptr && board[finalRow][finalCol]->color == p->color) {
                return false;
            }

            bool isSthBlocking = pieceBlockingStraight(startRow, startCol, finalRow, finalCol);

            if(isSthBlocking) {
                return false;
            }

            else {
                finalRow = startRow;
                finalCol = startCol;
                return true;
            }
        }

        return false;
    }

    else if(p->type == pieceType::knight) {

        if(board[finalRow][finalCol] != nullptr && board[finalRow][finalCol]->color == p->color) {
            return false;
        }

        int rowDiff = abs(finalRow - startRow);
        int colDiff = abs(finalCol - startCol);

        if((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
            finalRow = startRow;
            finalCol = startCol;
            return true;
        }

        else {
            return false;
        }
    }

    else if(p->type == pieceType::bishop) {

        if(board[finalRow][finalCol] != nullptr && board[finalRow][finalCol]->color == p->color) {
            return false;
        }

        if(abs(finalRow - startRow) == abs(finalCol - startCol)) {
            if(pieceBlockingDiagonal(startRow, startCol, finalRow, finalCol)) {
                return false;
            }

            else {
                finalRow = startRow;
                finalCol = startCol;
                return true;
            }
        }

        else {
            return false;
        }
    }

    else if(p->type == pieceType::queen) {

        if(board[finalRow][finalCol] != nullptr && board[finalRow][finalCol]->color == p->color) {
            return false;
        }

        bool isStraight = (startCol == finalCol || startRow == finalRow)? true : false;
        bool isDiagonal = (abs(finalRow - startRow) == abs(finalCol -  startCol))? true : false;

        if(isStraight) {

            if(pieceBlockingStraight(startRow, startCol, finalRow, finalCol)) {
                return false;
            }

            else {
                finalRow = startRow;
                finalCol = startCol;
                return true;
            }
        }

        else if(isDiagonal) {

            if(pieceBlockingDiagonal(startRow, startCol, finalRow, finalCol)) {
                return false;
            }

            else {
                finalRow = startRow;
                finalCol = startCol;
                return true;
            }
        }

        else {
            return false;
        }
    }

    else if (p->type == pieceType::king) {

        if(board[finalRow][finalCol] != nullptr && board[finalRow][finalCol]->color == p->color) {
            return false;
        }

        int colMove = abs(startCol - finalCol);
        int rowMove = abs(startRow - finalRow);
        
        if((rowMove == 0 && colMove == 0)) {
            return false;
        }

        else if((colMove <= 1 && rowMove <= 1)) {
            finalRow = startRow;
            finalCol = startCol;
            return true;
        }

        else if(rowMove == 0 && colMove == 2) {
            bool kingMoved = (p->color == pieceColor::white) ? whiteKingMoved : blackKingMoved;

            if(kingMoved) {
                return false;
            }

            if(isInCheck(p->color)) return false;

            if(finalCol > startCol) {
                bool rookMoved = (p->color == pieceColor::white) ? whiteRookRightMoved : blackRookRightMoved;

                if(rookMoved) {
                    return false;
                }

                if(board[startRow][startCol + 1] != nullptr) {
                    return false;
                }

                if(board[startRow][startCol + 2] != nullptr) {
                    return false;
                }

                board[startRow][startCol + 1] = board[startRow][startCol];
                board[startRow][startCol] = nullptr;

                bool passingCheck = isInCheck(p->color);

                board[startRow][startCol] = board[startRow][startCol + 1];
                board[startRow][startCol + 1] = nullptr;

                if(passingCheck) {
                    return false;
                }

                return true;
            }

            else {
                bool rookMoved = (p->color == pieceColor::white) ? whiteRookLeftMoved : blackRookLeftMoved;

                if(rookMoved) {
                    return false;
                }

                if(board[startRow][startCol - 1] != nullptr) {
                    return false;
                }

                if(board[startRow][startCol - 2] != nullptr) {
                    return false;
                }

                board[startRow][startCol - 1] = board[startRow][startCol];
                board[startRow][startCol] = nullptr;

                bool passingCheck = isInCheck(p->color);

                board[startRow][startCol] = board[startRow][startCol - 1];
                board[startRow][startCol - 1] = nullptr;

                if(passingCheck) {
                    return false;
                }

                return true;
            }
        }

        else {
            return false;
        }
    }

    else {
        return false;
    }
}

std::string Game::getBoardHash() {
    std::string hash = "";

    for(int row = 0; row < 8; row++) {

        for(int col = 0; col < 8; col++) {

            if(board[row][col] == nullptr) {
                hash += "--";
            } 
            
            else {
                hash += (board[row][col]->color == pieceColor::white) ? "w" : "b";

                switch(board[row][col]->type) {
                    case pieceType::king:   
                        hash += "K"; 
                        break;
                    
                    case pieceType::queen:  
                        hash += "Q"; 
                        break;
                    
                    case pieceType::rook:   
                        hash += "R"; 
                        break;

                    case pieceType::bishop: 
                        hash += "B"; 
                        break;

                    case pieceType::knight: 
                        hash += "N"; 
                        break;

                    case pieceType::pawn:   
                        hash += "P"; 
                        break;
                }
            }
        }
    }

    hash += (currentTurn == pieceColor::white) ? "w" : "b";

    return hash;
}

bool Game::isStalemate(pieceColor color) {
    if(isInCheck(color)) {
        return false;
    }

    for(int startRow = 0; startRow < 8; startRow++) {
        for(int startCol = 0; startCol < 8; startCol++) {

            if(board[startRow][startCol] == nullptr) {
                continue;
            }

            if(board[startRow][startCol]->color != color) {
                continue;
            }

            for(int finalRow = 0; finalRow < 8; finalRow++) {

                for(int finalCol = 0; finalCol < 8; finalCol++) {

                    if(!performMoveValidation(startRow, startCol, finalRow, finalCol)) {
                        continue;
                    }

                    piece* captured = board[finalRow][finalCol];
                    board[finalRow][finalCol] = board[startRow][startCol];
                    board[startRow][startCol] = nullptr;

                    bool stillInCheck = isInCheck(color);

                    board[startRow][startCol] = board[finalRow][finalCol];
                    board[finalRow][finalCol] = captured;

                    if(!stillInCheck) {
                        return false;
                    }  
                }
            }
        }
    }

    return true;  
}

bool Game::isLegalMove(int startRow, int startCol, int finalRow, int finalCol) {

    if(!performMoveValidation(startRow, startCol, finalRow, finalCol)) {
        return false;
    }

    piece* captured = board[finalRow][finalCol];
    board[finalRow][finalCol] = board[startRow][startCol];
    board[startRow][startCol] = nullptr;

    bool inCheck = isInCheck(board[finalRow][finalCol]->color);

    board[startRow][startCol] = board[finalRow][finalCol];
    board[finalRow][finalCol] = captured;

    return !inCheck;
}

bool Game::isCheckmate(pieceColor color) {

    if(!isInCheck(color)) {
        return false;
    }

    for(int startRow = 0; startRow < 8; startRow++) {

        for(int startCol = 0; startCol < 8; startCol++) {

            if(board[startRow][startCol] == nullptr) {
                continue;
            }

            if(board[startRow][startCol]->color != color) {
                continue;
            }

            for(int finalRow = 0; finalRow < 8; finalRow++) {

                for(int finalCol = 0; finalCol < 8; finalCol++) {

                    if(!performMoveValidation(startRow, startCol, finalRow, finalCol)) {
                        continue;
                    }

                    piece* captured = board[finalRow][finalCol];
                    board[finalRow][finalCol] = board[startRow][startCol];
                    board[startRow][startCol] = nullptr;

                    bool stillInCheck = isInCheck(color);

                    board[startRow][startCol] = board[finalRow][finalCol];
                    board[finalRow][finalCol] = captured;

                    if(!stillInCheck) return false; 
                }
            }
        }
    }

    return true; 
}

bool Game::isInCheck(pieceColor color) {
    
    int kingRow, kingCol;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr && board[i][j]->type == pieceType::king && board[i][j]->color == color) {
                kingRow = i;
                kingCol = j;
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr && board[i][j]->color != color) {
                if(performMoveValidation(i, j, kingRow, kingCol)) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

bool Game::pieceBlockingDiagonal(int startRow, int startCol, int finalRow, int finalCol) {
    int rowDir = (finalRow > startRow) ? 1 : -1;
    int colDir = (finalCol > startCol) ? 1 : -1;
    
    int r = startRow + rowDir;
    int c = startCol + colDir;

    for(int i = 0; i < 7; i++) {

        if(r == finalRow && c == finalCol) {
            break;
        }

        if(board[r][c] != nullptr) {
            return true;
        }

        r += rowDir;
        c += colDir;
    }

    return false;
}

bool Game::pieceBlockingStraight(int startRow, int startCol, int finalRow, int finalCol) {
    piece* p = board[startRow][startCol];

    int checkValueCol = finalCol - startCol;
    bool isSthBlocking;

    //Checking where the rook is moving either veritically up and down or horizantally left and right
    if(checkValueCol > 0) {

        for(int i = startCol + 1; i < finalCol; i++) {

            if(board[finalRow][i] != nullptr) {
                return true; 
            }
        }
    }
    else if(checkValueCol < 0) {

        for(int i = startCol - 1; i > finalCol; i--) {

            if(board[finalRow][i] != nullptr) {
                return true;
            }
        }
    }

    else {
        int checkValueRow = finalRow - startRow;

        if(checkValueRow > 0) {

            for(int i = startRow + 1; i < finalRow; i++) {

                if(board[i][finalCol] != nullptr) {
                    return true;
                }
            }
        }

        else if(checkValueRow < 0) {

            for(int i = startRow - 1; i > finalRow; i--) {

                if(board[i][finalCol] != nullptr) {
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
        if((p->color == pieceColor::white && row == 0) || (p->color == pieceColor::black && row == 7)) {
            promotionRow = row;
            promotionCol = col;
            color = p->color;
            promotion = true;

            promotionPieces[0] = new piece(pieceType::queen, color);
            promotionPieces[1] = new piece(pieceType::rook, color);
            promotionPieces[2] = new piece(pieceType::knight, color);
            promotionPieces[3] = new piece(pieceType::bishop, color);
        }
    }
}

void Game::handlePromotionClick(int x, int y) {
    int clickedRow = y / 100;
    int clickedCol = x / 100;

    int startCol = (promotionCol <= 3) ? 0 : 4;
    pieceType chosenType;

    if(clickedRow == promotionRow) {
        if (clickedCol >= startCol && clickedCol <= startCol + 3) {

            for(int i = 0; i < 4; i++) {
                if(promotionPieces[i] == nullptr) {
                    return;
                }
            }

            int choice = clickedCol - startCol;

            switch (choice)
            {
                case 0:
                    delete board[promotionRow][promotionCol];
                    board[promotionRow][promotionCol] = new piece(pieceType::queen, color);
                    break;
                
                case 1:
                    delete board[promotionRow][promotionCol];
                    board[promotionRow][promotionCol] = new piece(pieceType::rook, color);
                    break;
                
                case 2:
                    delete board[promotionRow][promotionCol];
                    board[promotionRow][promotionCol] = new piece(pieceType::knight, color);
                    break;

                case 3:
                    delete board[promotionRow][promotionCol];
                    board[promotionRow][promotionCol] = new piece(pieceType::bishop, color);
                    break;
                
                default:
                    return;
            }

            for(int i = 0; i < 4; i++) {
                delete promotionPieces[i];
                promotionPieces[i] = nullptr;
            }

            promotion = false;

            isSelected = false;
            selectedColumn = -1;
            selectedRow = -1;

            currentTurn = (currentTurn == pieceColor::white) ? pieceColor::black : pieceColor::white;

            std::string hash = getBoardHash();
            positionHistory[hash]++;

            if(positionHistory[hash] >= 3) {
                gameOver = true;
                isDraw = true;
            }
        }
    }
}

Game::~Game() {

    for(int row = 0; row < 8; row++) {
        
        for(int col = 0; col < 8; col++) {
            delete board[row][col];
            board[row][col] = nullptr;
        }
    }

    for(int i = 0; i < 4; i++) {
        delete promotionPieces[i];
        promotionPieces[i] = nullptr;
    }
}