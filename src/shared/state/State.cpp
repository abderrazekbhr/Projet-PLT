#include "../state.h"
#include <iostream>
#include <vector>

state::State::State()
{
    turn = -1;
    initBoard();
    initCards();
    board = new GameBoard();
    allCards = new CardsDeck();
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
void state::State::initBoard()
{
    board = new GameBoard();
}
void state::State::initCards()
{
    allCards = new CardsDeck();
}
void state::State::addPlayer(std::string playerName)
{
    Player *player = new Player(playerName);
    players.push_back(player);
}
state::State::~State()
{
    delete board;
    delete allCards;
}
