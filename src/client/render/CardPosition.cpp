#include "CardPosition.h"

namespace render{

    CardPosition::CardPosition():x(0.0),y(0.0)
    {
    } 

    CardPosition::~CardPosition(){}

    void CardPosition::changePos()
    {
        x+=5;
        y+=3;
    }

    double CardPosition::getX()
    {
        return x;
    }

    double CardPosition::getY()
    {
        return y;
    }


}