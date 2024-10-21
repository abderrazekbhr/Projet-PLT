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

    if(collectedCard.empty())
    {
        cout << "Vous n'avez pas de cartes collectées \n" << endl;
    }

    for(const auto& card : collectedCard)
    {
       cout << "Card Number : " << to_string(card.getNumberCard()) << " Card Type : "<< to_string(card.getTypeCard()) << endl;        
    }
}

void Player::displayHoldCard ()
{
    cout << "Holded Cards " << endl;

    if(holdedCard.empty())
    {
        cout << "Vous ne possédez pas de cartes \n" << endl;
    }

    for(const auto& card : holdedCard)
    {
       cout << "Card : " << to_string(card.getTypeCard()) << endl;        
    }
}






