#include "render.h"
#include <iostream>
using namespace render;
static int nbInstance = 0;
CardShape::CardShape(float posX, float posY, float width, float height, std::string clearImg, bool isVisible)
{
    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->height = height;
    this->imgClear = clearImg;
    this->isVisible = isVisible;
    this->id = nbInstance;
    nbInstance++;
}

double CardShape::getX()
{
    return posX;
}
double CardShape::getY()
{
    return posY;
}
void CardShape::setX(double x)
{
    posX = x;
}
void CardShape::setY(double y)
{
    posY = y;
}
double CardShape::getWidth()
{
    return width;
}
double CardShape::getHeight()
{
    return height;
}

int CardShape::getId()
{
    return id;
}
void CardShape::changeVisibility()
{

    isVisible = !isVisible;
}

sf::Texture CardShape::createTexture(std::string img)
{
    sf::Texture texture;
    if (!texture.loadFromFile(img))
    {
        throw std::runtime_error("error can't load card texture " + img);
    }
    return texture;
}
void CardShape::setShapeProperty()
{
    try
    {
        if (isVisible)
        {
            sf::Texture texture = createTexture(imgClear);
            this->setTexture(&texture);
        }
        else
        {
            sf::Texture texture = createTexture(imgHidden);
            this->setTexture(&texture);
        }
        this->setSize({width, height});
        this->setPosition({posX, posY});
    }
    catch (std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

CardShape::~CardShape()
{
}