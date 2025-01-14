#include <iostream>
#include "render.h"
#include "state.h"

using namespace state;
int render::CardShape::nbInstance = 0;
std::string render::CardShape::imgHidden = "../assets/card/hidden.png";

render::CardShape::CardShape(float posX, float posY, float width, float height, std::string clearImg, bool isVisible, state::Card *card)
{
    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->height = height;
    this->imgClear = clearImg;
    this->isVisible = isVisible;
    this->id = nbInstance;
    this->cardInstance = card;
    nbInstance++;
}
render::CardShape::~CardShape()
{
}

double render::CardShape::getX()
{
    return posX;
}
double render::CardShape::getY()
{
    return posY;
}
void render::CardShape::setX(double x)
{
    posX = x;
}
void render::CardShape::setY(double y)
{
    posY = y;
}
double render::CardShape::getWidth()
{
    return width;
}
double render::CardShape::getHeight()
{
    return height;
}

int render::CardShape::getId()
{
    return id;
}
void render::CardShape::changeVisibility()
{

    isVisible = !isVisible;
}

sf::Texture render::CardShape::createTexture(std::string img)
{
    sf::Texture texture;
    if (!texture.loadFromFile(img))
    {
        throw std::runtime_error("error can't load card texture " + img);
    }
    return texture;
}
void render::CardShape::setShapeProperty()
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
bool render::CardShape::compare(state::Card *card)
{
    return cardInstance->equals(*card);
}
