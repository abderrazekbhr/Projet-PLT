#include "DistributeCardState.h"
#include "../state.h"
#include "Game.h"
#include <iostream>

using namespace state;

DistributeCardState::DistributeCardState() {
    std::cout << "DistributeCardState initialized..." << std::endl;
}

DistributeCardState::~DistributeCardState() {
    std::cout << "DistributeCardState destroyed..." << std::endl;
}

void DistributeCardState::handleRequest(std::vector<Player> &players) {

    if (Game::getListOfCards().size() < players.size() * 3) {
        std::cerr << " No more cards in the deck to distribute to each player. Round over." << std::endl;
        return;
    }


    for (auto& player : players) {
        for (int i = 0; i < 3; ++i) {

            Card card = Game::getListOfCards().back();
            player.getHoldCard().push_back(card);

            Game::getListOfCards().pop_back();
        }
    }

    std::cout << "Cards distributed to each player." << std::endl;
}