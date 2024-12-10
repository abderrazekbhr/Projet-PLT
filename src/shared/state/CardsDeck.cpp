#include "CardsDeck.h"
#include <iostream>
#include <algorithm>
#include <random>
#include "Player.h"
#include "GameBoard.h"

namespace state
{
    CardsDeck::CardsDeck()
    {
        for (int type = 1; type <= 4; type++)
        {
            for (int number = 1; number <= 10; number++)
            {
                allCards.emplace_back(static_cast<NumberCard>(number), static_cast<TypeCard>(type)); // Convert integer in correct type
            }
        }
    }

    CardsDeck::~CardsDeck()
    {
    }

    void CardsDeck::distributeCards(std::vector<Player *> players, int nbCards)
    {
        int sizeCards= allCards.size();
        int sizePlayers = players.size();
        if (sizeCards< sizePlayers * nbCards) // Check if the number of cards on the deck is enough
        {
            return;
        }
        else
        {
            for (auto &player : players)
            {
                for (int i = 0; i < nbCards; ++i)
                {
                    Card card = allCards.back();
                    player->addHoldedCard(card);
                    allCards.pop_back();
                }
            }
        }
    }

    void CardsDeck::distributeCardsOnBoard(GameBoard &board, int nbCards)
    {
        int sizeCards= allCards.size();
        if (sizeCards < nbCards)
        {
            return;
        }
        else
        {
            for (int i = 0; i < nbCards; ++i)
            {
                Card card = allCards.back();
                board.addCardToBoard(card);
                allCards.pop_back();
            }
        }
    }

    void CardsDeck::shuffleDeck()
    {
        std::random_device rd; // provides a source of entropy for a random generator.
        std::mt19937 g(rd());  // Generate random number based on Mersene Twister Algorithm
        std::shuffle(allCards.begin(), allCards.end(), g);
    }
}