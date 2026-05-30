#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "board.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 800}), "My Window", sf::Style::Titlebar | sf::Style::Close);

    while(window.isOpen()) {

        while (const auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(); 
        drawBoard(window);
        window.display();
    }
}