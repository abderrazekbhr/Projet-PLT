#include "../state.h"
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

//calculate the score for each player
        for (auto& player : players) {
            Game::CalculScorePlayer(player);
        }
}

}