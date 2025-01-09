#include "RandomAi.h"
#include "../engine/CaptureCard.h"
#include "../engine/ThrowCard.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace ai;
using namespace engine;
using namespace state;

RandomAi::RandomAi(std::string name) : AI(name)
{
    std::srand((unsigned int)std::time(0));
}

void RandomAi::run(engine::Engine *eng)
{

    state::State &currentState = eng->getState();
    state::Player &player = eng->getActualPlayer();
    state::GameBoard *board = currentState.getBoard();

    if (!board || player.getSizeHoldedCards() == 0)
    {
        return;
    }

    std::vector<state::Card> handCards = player.getHoldCard();
    std::vector<state::Card> boardCards = board->getCardBoard();

    // Utilisation de size_t pour les indices dans les boucles
    for (size_t i = 0; i < handCards.size(); i++)
    {
        for (size_t j = 0; j < boardCards.size(); j++)
        {
            if (handCards[i].getNumberCard() == boardCards[j].getNumberCard())
            {

                CaptureCard captureAction(static_cast<int>(i), {static_cast<int>(j)});
                eng->setActualCmd(&captureAction);
                if (captureAction.execute(eng))
                {
                    return;
                }
            }
        }
    }

    size_t randomIndex = std::rand() % handCards.size();
    ThrowCard throwAction(randomIndex);
    eng->setActualCmd(&throwAction);
    throwAction.execute(eng);
}

RandomAi::~RandomAi() {}
