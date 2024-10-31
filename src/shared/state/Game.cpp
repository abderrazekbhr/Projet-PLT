#include <vector>
#include "../state.h"
#include "Game.h"
#include <iostream>

using namespace std;
using namespace state;

Game::Game() {
    state = new WaitState();
    board = new GameBoard();
    for (int type = treffle; type <= coeur; ++type) {
        for (int number = un; number <= roi; ++number) {
            Card card(static_cast<NumberCard>(number), static_cast<TypeCard>(type));
            addCard(card);
        }
    }

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

void Game::addCard(Card &card) {
    listOfCards.push_back(card);
}


GameBoard * Game::getGameBoard() {
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

int Game::getMaxScore() {
    return maxScore;
}

void Game::setMaxScore(int maxScore) {
    Game::maxScore = maxScore;
}

std::vector<Card> Game::getListOfCards() {
    return listOfCards;
}