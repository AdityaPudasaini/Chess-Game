#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "piece.hpp"
#include "Game.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "My Window", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    Game game;

    while(window.isOpen()) {

        while (const auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) { // Closing logic
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                auto mouse = event->getIf<sf::Event::MouseButtonPressed>();
                int col = mouse->position.x / 100;
                int row = mouse->position.y / 100;
                game.userClick(row, col);
            }
        }

        window.clear(); 
        game.draw(window);
        window.display();
    }
}