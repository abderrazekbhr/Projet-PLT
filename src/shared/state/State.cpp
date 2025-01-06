#include "../state.h"
#include <iostream>
#include <vector>

state::State::State()
{
    turn = 0;
    maxScore = 0;
    playerIndexForLastCapturedCard = -1;
    nbPlayer = 0;
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
std::vector<state::Player *> state::State::getAllPlayers()
{
    return players;
}

void state::State::setPlayerIndexForLastCapturedCard(int newIndexPlayer)
{
    playerIndexForLastCapturedCard = newIndexPlayer;
}
int state::State::getPlayerIndexForLastCapturedCard()
{
    return playerIndexForLastCapturedCard;
}

state::State::~State()
{
    // delete board;
    // delete allCards;
    players.clear();
}