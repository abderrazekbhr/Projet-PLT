#include "RoundState.h"
#include "Player.h"
#include "GameBoard.h"
#include "Game.h"
#include <iostream>

namespace state
{

    RoundState::RoundState()
    {
        std::cout << "RoundState initialized..." << std::endl;
    }

    RoundState::~RoundState()
    {
        std::cout << "RoundState destroyed..." << std::endl;
    }

    void RoundState::handleRequest(std::vector<Player> &players)
    {
        while (true)
        {
            bool allHoldedCardsEmpty = true;

            for (auto &player : players)
            {
                if (!player.getHoldCard().empty())
                {
                    allHoldedCardsEmpty = false;
                    break;
                }
            }

            if (allHoldedCardsEmpty)
            {
                std::cout << "All players have played their cards.Round over!" << std::endl;
                break;
            }

            for (auto &player : players)
            {
                if (!player.getHoldCard().empty())
                {

                    player.play();

                    if (Game::getGameBoard()->getNumberCardBoard() == 0)
                    {
                        player.addToScore(1);
                        std::cout << player.getName() << " score incremented. New score: " << player.getScore() << std::endl;
                    }
                }
            }
        }
    }

}