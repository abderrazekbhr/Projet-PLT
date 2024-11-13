#include "../state.h"
#include <iostream>
#include <vector>

namespace state {
    EndGameState::EndGameState() {
        std::cout << "EndGameState initialized..." << std::endl;
    }

    EndGameState::~EndGameState() {
        std::cout << "EndGameState destroyed..." << std::endl;
    }

    void CountScoreState::handleRequest(std::vector<Player>& players) {
        int maxScore = Game::getMaxScore();
        Player* winner = nullptr;
        std::vector<Player*> potentialWinners;
        std::vector<Player*> losers;

//Determine the players who surpass the target score set by the main player at the beginning ( either 11 or 21)
    for (auto& player : players) {
        int score = player.getScore();
        std::cout << player.getName() << " has a score of " << score << "." << std::endl;

        if (score >= maxScore) {
            potentialWinners.push_back(&player);
        }
    }
//Determine the player with the highest score among the players who have surpassed the target score, that player is the final winner                       among the players
    if (!potentialWinners.empty()) {
        int highestScore = 0;
        for (const auto& player : potentialWinners) {
            if (player->getScore() > highestScore) {
                highestScore = player->getScore();
            }
        }

        for (const auto& player : potentialWinners) {
            if (player->getScore() == highestScore) {
                if (winner == nullptr) {
                    winner = player;
                }
            }
        }

        if (winner) {
            std::cout << "The winner is " << winner->getName() << " with a score of " << winner->getScore() << "!" << std::endl;
            std::vector<Player*> tiedPlayers;
// Determine the players who have the same score as the final winner
            for (const auto& player : potentialWinners) {
                if (player->getScore() == winner->getScore()) {
                    tiedPlayers.push_back(player);
                }
            }

            if (tiedPlayers.size() > 1) {
                std::cout << "Note: There is a tie among players: ";
                for (const auto& tiedPlayer : tiedPlayers) {
                    std::cout << tiedPlayer->getName() << " ";
                }
                std::cout << "with a score of " << winner->getScore() << "!" << std::endl;
            }
        }
    } else {
        std::cout << "No winner this round." << std::endl;
    }
//Determine the players who have lost, meaning their score is lower than the target score,
//as well as the players who have surpassed the target score but have a lower score than the final winner
    for (auto& player : players) {
        if (player.getScore() < maxScore ||
            (winner && player.getScore() != winner->getScore())) {
            losers.push_back(&player);
        }
    }

    if (!losers.empty()) {
        std::cout << "The losers are: ";
        for (const auto& loser : losers) {
            std::cout << loser->getName() << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "All players are winners!" << std::endl;
    }
}

}