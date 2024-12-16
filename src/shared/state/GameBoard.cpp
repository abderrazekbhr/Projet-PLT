#include <iostream>
#include <vector>
#include "GameBoard.h"
#include "Card.h"

namespace state
{
    GameBoard::GameBoard()
    {
    }

    GameBoard::~GameBoard()
    {
        cardsOnBoard.clear();
    }

    int GameBoard::getNumberCardBoard()
    {
        return this->cardsOnBoard.size();
    }

    void GameBoard::addCardToBoard(Card card)
    {
        cardsOnBoard.push_back(card);
    }

    void GameBoard::removeCardBoard(Card card)
    {
        for (auto it = cardsOnBoard.begin(); it != cardsOnBoard.end();)
        {
            if (it->equals(card))
            {
                it = cardsOnBoard.erase(it); // Met à jour l'itérateur après suppression
            }
            else
            {
                ++it; // Incrémente si pas de suppression
            }
        }
    }

    std::vector<Card> GameBoard::getCardBoard()
    {
        return cardsOnBoard;
    }
}
