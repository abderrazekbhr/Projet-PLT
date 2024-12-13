#include "CardsDeck.h"
#include <iostream>
#include <algorithm>
#include <random>
#include<chrono>
#include "Player.h"
#include "GameBoard.h"

namespace state
{
    CardsDeck::CardsDeck()
    {
        for (int type = treffle; type <= coeur; ++type) {
            for (int number = un; number <= roi; ++number) {
                Card card(static_cast<NumberCard>(number), static_cast<TypeCard>(type));
                allCards.push_back(card);
            }
        }
    }

    CardsDeck::~CardsDeck()
    {
    }

    void CardsDeck::distributeCards(std::vector<Player *> players, int nbCards)
    {

        int sizePlayers = players.size();
        if (getDeckSize()< sizePlayers * nbCards) // Check if the number of cards on the deck is enough
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

        if (getDeckSize() < nbCards)
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
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed);
        std::shuffle(allCards.begin(), allCards.end(), generator);
    }

    int CardsDeck::getDeckSize() {
        return allCards.size();
    }
    std::vector<Card> CardsDeck::getAllCards() {
        return allCards;
    }

}
