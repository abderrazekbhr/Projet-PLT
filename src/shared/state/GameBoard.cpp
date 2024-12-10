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
    // Prompts the player to select cards from the game board
    std::vector<Card> GameBoard::selectCardFromBoard(std::vector<int> cardIndexs)
    {
        std::vector<Card> selectedCard;
        for (int index : cardIndexs)
        {
            selectedCard.push_back(cardsOnBoard[index]);
        }
        // set<int> cardIndex;
        // bool needToSelect = true;
        // string answer;
        // int boardSize = Game::getGameBoard()->getCardBoard().size(); // TODO: make method getBoardSize()
        // if (boardSize == 0)
        // {
        //     cout << "*********** The board is empty ***********" << endl;
        //     return selectedCard;
        // }

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