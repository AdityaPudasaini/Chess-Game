#include "piece.hpp"
#include <iostream>
#include <filesystem>

piece::piece (pieceType type, pieceColor color) {
    this->type = type;
    this->color = color;

    // FInalizing the color of the piece
    std::string actualColor;

    if(color == pieceColor::white) {
        actualColor = "w";
    }

    else {
        actualColor = "b";
    }

    //Finalizing type of piece
    std::string actualType;

    switch(type)
    {
        case pieceType::pawn:
            actualType = "P";
            break;

        case pieceType::rook:
            actualType = "R";
            break;
        
        case pieceType::knight:
            actualType = "N";
            break;
        
        case pieceType::bishop:
            actualType = "B";
            break;
        
        case pieceType::queen:
            actualType = "Q";
            break;
        
        case pieceType::king:
            actualType = "K";
            break;
    }

    std::string actualPath;
    actualPath = "./assets/" + actualColor + actualType + ".png";

    if(!(texture.loadFromFile(actualPath))) {
        throw std::runtime_error("Failed to load texture: " + actualPath);
    }

    sprite.emplace(texture);
}

void piece::draw(sf::RenderWindow& window, int row, int col) {
    
    sf::Vector2u size = sprite->getTexture().getSize();
    sprite->setScale({100.f / size.x, 100.f / size.y});
    
    sprite->setPosition({col * 100.f, row * 100.f});
    window.draw(*sprite);
}