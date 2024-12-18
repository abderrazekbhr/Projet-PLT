#include "RoundDistributeCards.h"

namespace engine
{

    RoundDistributeCards::RoundDistributeCards()
    {
        this->setNewCMD(DISTRIBUTE_CARD);
    }
    RoundDistributeCards::~RoundDistributeCards() {}

    bool RoundDistributeCards::execute(Engine *engine)
    {

        state::State &currentState = engine->getState();

        // Distribute 3 cards to each player
        currentState.getAllCards()->distributeCards(currentState.getAllPlayers(), 3);
        return true;
    }

}