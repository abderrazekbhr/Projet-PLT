#include <iostream>
#include <vector>
#include "../state.h"

using namespace state;
using namespace std;

Card::Card(NumberCard number, TypeCard type)
{
    this->typeOfCard = type;
    this->numberOfCard = number;
}

NumberCard Card::getNumberCard()
{
    return this->numberOfCard;
}

TypeCard Card::getTypeCard()
{
    return this->typeOfCard;
}

bool Card::equals(Card other)
{
    return (this->getNumberCard() == other.numberOfCard && this->getTypeCard() == other.typeOfCard);
}

Card::~Card()
{
    
}


