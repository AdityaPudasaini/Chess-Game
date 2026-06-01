#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "piece.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "My Window", sf::Style::Titlebar | sf::Style::Close);
    piece testPiece(pieceType::pawn, pieceColor::white);

    while(window.isOpen()) {

        while (const auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) { // Closing logic
                window.close();
            }
        }

        window.clear(); 
        drawBoard(window);
        testPiece.draw(window, 6, 0);
        window.display();
    }
}