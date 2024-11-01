#include <iostream>
#include <vector>
#include "state.h"

using namespace state;
using namespace std;
int Card::nbCardInstrance = 0;

Card::Card(NumberCard number, TypeCard type)
{
    this->nbCardInstrance++;
    this->typeOfCard = type;
    this->numberOfCard = number;
}

NumberCard Card::getNumberCard() const
{
    return this->numberOfCard;
}

TypeCard Card::getTypeCard() const
{
    return this->typeOfCard;
}

bool Card::operator==(const Card& other) const
{
    return (this->getNumberCard()==other.numberOfCard && this->getTypeCard() == other.typeOfCard);
} 

Card::~Card()
{

}