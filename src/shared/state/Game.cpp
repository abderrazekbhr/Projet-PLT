#include <vector>
#include "../state.h"
#include "Game.h"
#include <iostream>
using namespace std;
using namespace state;

Game::Game() {
    state = new WaitState();
    board = new GameBoard();

}

void Game::setState(State* state) {
    delete this->state;
    this->state = state;
}

void Game::request() {
    this->state->handleRequest(players);
}

Game::~Game() {
    delete state;

}

void Game::addPlayer(Player& player) {
    players.push_back(player);
}

GameBoard* Game::getGameBoard() {
    return board;
}

void Game::displayPlayers() {
    cout << "Players are : "  << endl;
    for (size_t i = 0; i < players.size(); ++i) {
        cout << "Player " << i + 1 << ": " << players[i].getName() << endl;
        players[i].displayHoldCard();
        players[i].displayCollectCard();
    }
}