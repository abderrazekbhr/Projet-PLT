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

<<<<<<< HEAD
<<<<<<< HEAD
// void GameBoard::displayCardsOnBoard()
// {
//     std::cout<<"Cards on Boad : ";
//     for (const Card& card : cardsOnBoard)
//     {
//         std::cout<< "[" << card.getNumberCard() << "||" << card.getTypeCard() << "]";
//     }
//     std::cout<<std::endl;
// }
=======
>>>>>>> b5e1e6b16a45180c333ea9d1655340ab60739614
=======
        // cout << "*********** Choose a card index from the board between 1 and " << boardSize << " ***********" << endl;
        // for (Card &card : Game::getGameBoard()->getCardBoard()) // Use const reference // to do //
        // {
        //     cout << "[" << card.getNumberCard() << "|" << card.getTypeCard() << "], ";
        // }
        // cout << endl;

        // while (needToSelect)
        // {
        //     cout << "*********** Do you want to choose any card from the board? (yes/no) ***********" << endl;
        //     cin >> answer;
        //     if (answer == "no")
        //         break;

        //     int index = -1;
        //     // TODO:create a function that isAvailableCardInBoard()
        //     while (!(cin >> index) || cardIndex.count(index) || index < 0 || index >= boardSize)
        //     {
        //         cout << "*********** Enter a valid index between 0 and " << boardSize - 1 << " (not already selected) ***********" << endl;
        //         cin.clear();
        //         cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //     }
        //     cardIndex.insert(index); // Insert directly
        //     selectedCard.push_back(Game::getGameBoard()->getCardBoard()[index]);
        // }

        return selectedCard; // Returns the selected cards
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
}
>>>>>>> df043d9d77211bd4375cc581b5bea3cdfe49e5bd
