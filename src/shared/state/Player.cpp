#include <iostream>
#include <vector>
#include "state.h"

using namespace state;
using namespace std;
int nbPlayerInstance = 0;
Player::Player()
{
    this->nbPlayerInstance++;
    this->name = "Player " + to_string(this->idPlayer);
    this->idPlayer = this->nbPlayerInstance;
    this->totalScore = 0;
}

// getters
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

int Player::getTotalCollectCard()
{
    return collectedCard.size();
}

int Player::getTotalHoldCard()
{
    return holdedCard.size();
}

// Setters
void Player::setName(std::string name)
{
    name = this->name;
}

void Player::displayCollectCard()
{
    cout << "Collected Cards " << endl;

    if (collectedCard.empty())
    {
        cout << "Vous n'avez pas de cartes collectées \n"
             << endl;
    }

    for (const auto &card : collectedCard)
    {
        cout << "[" << card.get()->getNumberCard() << "|" << card.get()->getTypeCard() << "] ,";
    }
}

void Player::displayHoldCard()
{
    cout << "Holded Cards " << endl;

    if (holdedCard.empty())
    {
        cout << "Vous ne possédez pas de cartes \n"
             << endl;
    }

    for (const auto &card : holdedCard)
    {
        cout << "[" << card.get()->getNumberCard() << "|" << card.get()->getTypeCard() << "] ,";
    }
}
void Player::addToScore(int points)
{
    this->totalScore += points;
}

void Player::playCard(std::vector<Card> selectedCard)
{
    for (const auto &card : selectedCard)
    {
        this->holdedCard.push_back(card);
    }
}
Player::~Player()
{
    this->collectedCard.clear();
    this->holdedCard.clear();
    this->totalScore = 0;
}