#include "board.hpp"

void drawBoard(sf::RenderWindow& window) {

    //Colors for the board

    sf::Color white(255, 255, 255);
    sf::Color black (0, 0, 0);

    // Making the rectangle for the board

    sf::RectangleShape boardShape({100.f, 100.f});

    for (int row = 0; row < 8; row++) {

        for (int col = 0; col < 8; col++) {

            if ((row + col) % 2 == 0) {
                boardShape.setFillColor(white);
            }

            else {
                boardShape.setFillColor(black);
            }

            boardShape.setPosition({col * 100.f, row * 100.f});
            window.draw(boardShape);
        }
    }

}