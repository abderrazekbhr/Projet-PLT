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

    void GameBoard::deleteCard(Card card)
    {
        for (auto it = cardsOnBoard.begin(); it != cardsOnBoard.end(); it++)
        {
            if (*it == card)
            {
                cardsOnBoard.erase(it);
            }
        }
    }

// void GameBoard::displayCardsOnBoard()
// {
//     std::cout<<"Cards on Boad : ";
//     for (const Card& card : cardsOnBoard)
//     {
//         std::cout<< "[" << card.getNumberCard() << "||" << card.getTypeCard() << "]";
//     }
//     std::cout<<std::endl;
// }

 };