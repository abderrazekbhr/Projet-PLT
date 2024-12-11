#include <iostream>
#include <vector>
#include <set>
#include "state.h"
#include <limits>
#include <algorithm>

using namespace std;
using namespace state;

Player::Player(string name)
{
    this->name = name;
    totalScore = 0;
}

// Returns the name of the player
string Player::getName() { return name; }

// Returns the total score of the player
int Player::getScore() { return totalScore; }

// Returns the list of collected cards
vector<Card> Player::getCollectCard() { return collectedCard; }

// Returns the list of held cards
vector<Card> Player::getHoldCard() { return holdedCard; }

PlayerStatus Player::getPlayerStatus()
{
    return status;
}
// Setters
// Sets the name of the player
void Player::setName(string name) { this->name = name; }

// Adds a card to the list of collected cards
void Player::addHoldedCard(Card card)
{
    holdedCard.push_back(card);
}

// Adds points to the player's total score
void Player::addToScore(int points) { totalScore += points; }

// Prompts the player to select a card from their hand
Card Player::selectCardFromHand(int cardIndex)
{
    return holdedCard[cardIndex];
}

// Removes a specified card from the player's hand
void Player::removeCardFromHand(Card card)
{
    auto it = remove_if(holdedCard.begin(), holdedCard.end(),
                        [&](Card &c)
                        {
                            return c.getNumberCard() == card.getNumberCard() &&
                                   c.getTypeCard() == card.getTypeCard();
                        });

    holdedCard.erase(it, holdedCard.end()); // Use erase-remove idiom
}

void Player::addCollectedCard(Card card)
{
    collectedCard.push_back(card);
}

void Player::addHoldCard(Card card)
{
    holdedCard.push_back(card);
}

int Player::getSizeHoldedCards()
{
    return holdedCard.size();
}

int Player::getSizeCollectedCards()
{
    return collectedCard.size();
}

void Player::setPlayerStatus(PlayerStatus newStatus)
{
    status = newStatus;
}

Player::~Player()
{
    collectedCard.clear();
    holdedCard.clear();
    totalScore = 0;
}