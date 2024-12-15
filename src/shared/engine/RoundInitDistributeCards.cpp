#include "RoundInitDistributeCards.h"
#include "state/Player.h"

namespace engine
{
    RoundInitDistributeCards::RoundInitDistributeCards(char response) {
        this->response = response;
    }
    RoundInitDistributeCards::~RoundInitDistributeCards() {}

    bool RoundInitDistributeCards::execute(Engine *engine)
    {
        state::State &currentState = engine->getState();

        state::CardsDeck *allCards = currentState.getAllCards();
        allCards->shuffleDeck();

        if (response == 'y' || response == 'Y')
        {

            allCards->distributeCards(currentState.getAllPlayers(), 3);
            allCards->distributeCardsOnBoard(*(currentState.getBoard()), 4);
        }
        else
        {
            allCards->distributeCardsOnBoard(*(currentState.getBoard()), 4);
            allCards->distributeCards(currentState.getAllPlayers(), 3);
        }
        return true;
    }
}
