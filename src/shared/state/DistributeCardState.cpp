#include "DistributeCardState.h"
#include "../state.h"
#include "Game.h"
#include <iostream>
#include <vector>
namespace state
{

    DistributeCardState::DistributeCardState()
    {
        std::cout << "DistributeCardState initialized..." << std::endl;
    }

    DistributeCardState::~DistributeCardState()
    {
        std::cout << "DistributeCardState destroyed..." << std::endl;
    }

    void DistributeCardState::handleRequest(std::vector<Player> &players)
    {
        // Before dealing the cards, we must check if there are still cards left in the initial deck. If not, the game is over
        if (Game::getListOfCards().size() < players.size() * 3)
        {
            std::cerr << " No more cards in the deck to distribute to each player. Game over." << std::endl;
            return;
        }

        // Distribute 3 cards to each player
        for (auto &player : players)
        {
            for (int i = 0; i < 3; ++i)
            {

                Card card = Game::getListOfCards().back();
                player.addHoldedCard(card);

                Game::getListOfCards().pop_back();
            }
        }

        std::cout << "Cards distributed to each player." << std::endl;
    }
}