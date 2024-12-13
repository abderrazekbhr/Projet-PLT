#include "../state.h"
#include <iostream>
#include <vector>

state::State::State()
{
    turn = -1;
    maxScore=0;
    nbPlayer=0;
    initBoard();
    initCards();


}

state::GameBoard *state::State::getBoard()
{
    return this->board;
}
state::CardsDeck *state::State::getAllCards()
{
    return allCards;
}
int state::State::getMaxScore()
{
    return maxScore;
}
int state::State::getNbPlayer()
{
    return nbPlayer;
}
void state::State::setMaxScore(int newMaxScore)
{
    maxScore = newMaxScore;
}
void state::State::setNbPlayer(int newNbPlayer)
{
    nbPlayer = newNbPlayer;
}
int state::State::incrementTurn()
{
    turn = (turn + 1) % nbPlayer;
    return turn;

}
void state::State::initBoard() {
    if (board == nullptr) {
        board = new GameBoard();
    }
}

void state::State::initCards() {
    if (allCards == nullptr) {
        allCards = new CardsDeck();
    }
}

void state::State::addPlayer(std::string playerName)
{
    Player *player = new Player(playerName);
    players.push_back(player);
}
std::vector<state::Player *> state::State::getAllPlayers() {
    return players;
}
state::State::~State() {






    for (Player* player : players) {

        delete player;
    }

    players.clear();
}
