#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "piece.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "My Window", sf::Style::Titlebar | sf::Style::Close);
    piece* board[8][8] = {nullptr};

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

    window.setFramerateLimit(60);

    while(window.isOpen()) {

        while (const auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) { // Closing logic
                window.close();
            }
        }

        window.clear(); 
        drawBoard(window);

        for(int row = 0; row < 8; row++) {
            for(int col = 0; col < 8; col++) {
                if(board[row][col] != nullptr) {
                    board[row][col]->draw(window, row, col);
                }
            }
        }

        window.display();
    }
}