#include "render.h"
#include "CardPosition.h"
#include <SFML/Graphics.hpp>

namespace render
{

    // Default constructor initializing position to (0, 0)
    CardPosition::CardPosition() : x(0.0), y(0.0) {}

    // Destructor
    CardPosition::~CardPosition() {}

    // Method to adjust position by fixed increments
    void CardPosition::changePos()
    {
        x += 5.0; // Increment x-coordinate
        y += 3.0; // Increment y-coordinate
    }

    // Setter for position
    void CardPosition::setPosition(double newX, double newY)
    {
        x = newX;
        y = newY;
    }

    // Getter for x-coordinate
    double CardPosition::getX()
    {
        return x;
    }

    // Getter for y-coordinate
    double CardPosition::getY()
    {
        return y;
    }

    // Method to calculate the position of a card based on its index
    // sf::Vector2f CardPosition::getCardPosition(int index, double cardWidth, double cardHeight)
    // {
    //     double spacing = 15.0;                                 // Space between cards
    //     double cardPosX = x + (index * (spacing + cardWidth)); // Calculate X position
    //     double cardPosY = y;                                   // Y position remains constant

    //     return sf::Vector2f(static_cast<float>(cardPosX), static_cast<float>(cardPosY));
    // }

    // // Method to calculate the position of a card on the board based on its index
    // sf::Vector2f CardPosition::getBoardPosition(int index, double cardWidth, double cardHeight)
    // {
    //     double spacing = 10.0;                                  // Space between cards on the board
    //     double boardPosX = x + (index * (cardWidth + spacing)); // Calculate X position
    //     double boardPosY = y;                                   // Y position remains constant

    //     return sf::Vector2f(static_cast<float>(boardPosX), static_cast<float>(boardPosY));
    // }
}
