#include "CountScoreState.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <vector>

namespace state {

CountScoreState::CountScoreState() {
    std::cout << "CountScoreState initialized..." << std::endl;
}

CountScoreState::~CountScoreState() {
    std::cout << "CountScoreState destroyed..." << std::endl;
}

void CountScoreState::handleRequest(std::vector<Player>& players) {
    int maxScore = Game::getMaxScore();
    Player* winner = nullptr;
    std::vector<Player*> potentialWinners;
    std::vector<Player*> losers;

    for (auto& player : players) {
        int score = player.getScore();
        std::cout << player.getName() << " has a score of " << score << "." << std::endl;

        if (score >= maxScore) {
            potentialWinners.push_back(&player);
        }
    }

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
