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
        for (auto it = cardsOnBoard.begin(); it != cardsOnBoard.end(); it++)
        {
            if (it->equals(card))
            {
                cardsOnBoard.erase(it);
            }
        }
    }

    std::vector<Card> GameBoard::getCardBoard()
    {
        return cardsOnBoard;
    }
}
