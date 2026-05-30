#pragma once
#include <SFML/Graphics.hpp>

void drawBoard(sf::RenderWindow& window); // Referencing to the window instead of coping so that
                                          // we can work on the same one