#include <iostream>
#include "CardShape.h"

namespace render
{

    std::string CardShape::imgHidden = "../assets/cards/hidden.png";

    CardShape::CardShape(int index,float posX, float posY, float width, float height, std::string clearImg, bool isVisible, state::Card *card)

    {
        this->posX = posX;
        this->posY = posY;
        this->width = width;
        this->height = height;
        this->imgClear = clearImg;
        this->isVisible = isVisible;
        this->cardInstance = card;
        setShapeProperty(); // Initialise les propriétés
    }

    CardShape::~CardShape() = default;

    double CardShape::getX() { return posX; }
    double CardShape::getY() { return posY; }
    void CardShape::setX(double x) { posX = x; }
    void CardShape::setY(double y) { posY = y; }
    double CardShape::getWidth() { return width; }
    double CardShape::getHeight() { return height; }

    void CardShape::changeVisibility()
    {
        isVisible = !isVisible;
        setShapeProperty(); // Met à jour la texture lorsque la visibilité change
    }

    void CardShape::createTexture(std::string img)
    {
        if (!texture.loadFromFile(img))
        {
            throw std::runtime_error("Error: Can't load card texture " + img);
        }
    }

    void CardShape::setShapeProperty()
    {
        try
        {
            std::string texturePath = isVisible ? imgClear : imgHidden;

            if (!texture.loadFromFile(texturePath))
            {
                throw std::runtime_error("Error: Can't load card texture " + texturePath);
            }

            this->setTexture(&texture);
            this->setSize({width, height});
            this->setPosition({posX, posY});
        }
        catch (std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    bool CardShape::compare(state::Card *card)
    {
        if (!cardInstance || !card)
            return false;
        return cardInstance->equals(*card);
    }

} // namespace render
