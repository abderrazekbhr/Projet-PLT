#include "../state.h"
#include <iostream>
#include <vector>

state::State::State()
{
<<<<<<< HEAD
    turn = -1;
    maxScore = 0;
    nbPlayer = 0;
=======
    turn = 0;
    maxScore = 0;
    nbPlayer = 0;
>>>>>>> 3fe0b4a0f226e96f3ff5220681d08597e52d4a69
    initBoard();
    initCards();
<<<<<<< HEAD
=======

<<<<<<< HEAD
>>>>>>> 7c2ab0729647b252ef440a147121404067deb108
=======

>>>>>>> 9488189cf02f95e2318cce19863fbd21282d9ff7
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
    if (board == nullptr)
    {
        board = new GameBoard();
    }
}

void state::State::initCards()
{
    if (allCards == nullptr)
    {
        allCards = new CardsDeck();
    }
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
state::State::~State()
{
    players.clear();
}
