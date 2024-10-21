#include <iostream>
#include <vector>
#include "state.h"

using namespace state;
using namespace std;    

Player::Player()
{
    this->name="Player " + to_string(rand());
    cout << "\n" << endl; 
}

//getters
int Player::getIdPlayer()
{
    return this->idPlayer;
}

string Player::getName()
{
    return this->name;
}

int Player::getScore()
{
    return this->totalScore;
}

int Player::getTotalCollectCard ()
{
    return collectedCard.size();
}

int Player::getTotalHoldCard ()
{
    return holdedCard.size();
}

//Setters
void Player::setName (std::string name)
{
    name=this->name;
}

void Player::displayCollectCard ()
{
    cout << "Collected Cards " << endl;

    for(const auto& card : collectedCard)
    {
       cout << "Card : " << card << endl;        
    }
}

void Player::displayHoldCard ()
{
    cout << "Holded Cards " << endl;

    for(const auto& card : holdedCard)
    {
       cout << "Card : " << card.getTypeCard() << endl;        
    }
}






