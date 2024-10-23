#include <iostream>
#include <vector>
#include "state.h"

using namespace state;
using namespace std;
int Card::nbCardInstrance = 0;
Card::Card(NumberCard number, TypeCard type)
{
    this->nbCardInstrance++;
    this->idCard = this->nbCardInstrance;
    this->typeOfCard = type;
    this->numberOfCard = number;
}

int Card::getIdCard()
{
    return this->idCard;
}

NumberCard Card::getNumberCard()
{
    return this->numberOfCard;
}

TypeCard Card::getTypeCard()
{
    return this->typeOfCard;
}