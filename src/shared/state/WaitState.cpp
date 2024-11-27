#include "../state.h"
#include <iostream>

state::WaitState::WaitState() {
    std::cout << "WaitState initialized." << std::endl;
}

state::WaitState::~WaitState() {
    std::cout << "WaitState destroyed." << std::endl;
}
// create first player and his waiting for the game
void state::WaitState::handleRequest(std::vector<Player> &players) {
    Player* newPlayer = new Player();
    // Add the new player to the game
    Game::addPlayer(*newPlayer);
    std::cout << "Game State : Waiting with " << players.size() << " players." << std::endl;

}