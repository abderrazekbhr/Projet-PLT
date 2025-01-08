#include "RoundInitDistributeCards.h"
#include "state/Player.h"

namespace engine
{
    RoundInitDistributeCards::RoundInitDistributeCards(char response)
    {
        this->response = response;
        this->setNewCMD(FIRST_DISTRIBUTION);
    }
    RoundInitDistributeCards::~RoundInitDistributeCards() {}
    
    // TODO: Correct logic in this method : we get the first card and then ask the player if he wants to take it or not
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
