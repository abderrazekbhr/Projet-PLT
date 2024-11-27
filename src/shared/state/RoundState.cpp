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
        // Make sure that at least one player has a card to play in order to continue the round
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
            // if all players have no cards left to play, the round is over
            if (allHoldedCardsEmpty)
            {
                std::cout << "All players have played their cards.Round over!" << std::endl;
                break;
            }

            // Each player plays a card and, at each turn , checks if the board is empty.
            // if the board is empty, they add +1 to their score. This count as a Chkoba
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