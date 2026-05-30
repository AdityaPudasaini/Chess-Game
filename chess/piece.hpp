#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>

enum class pieceType {
    king, queen, bishop, rook, knight, pawn
};

enum class pieceColor {
    white, black
};

struct piece {
    pieceType type;
    pieceColor color;
    sf::Texture texture; // Loads the image into memory
    sf::Sprite sprite; // Displays the image into the screen

    piece (pieceType type, pieceColor color);

    void draw(sf::RenderWindow& window, int row, int col);
};