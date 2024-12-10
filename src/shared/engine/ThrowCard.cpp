#include "ThrowCard.h"
#include "Command.h"
#include <stdexcept>
using namespace engine;

ThrowCard::ThrowCard(int indexCardHand)
{
    this->indexCardHand = indexCardHand;
}
bool ThrowCard::execute(Engine *engine)
{

    try
    {
        state::Player player = engine->getActualPlayer();
        bool isValidCard = this->validateCardHand(indexCardHand, player.getHoldCard().size());// TODO: getnumber of cards in hand
        state::State currentState = engine->getState();
        state::Card card = player.getHoldCard()[indexCardHand];
        player.removeCardFromHand(card);
        currentState.getBoard().addCardToBoard(card);
        engine->setNextPlayer();
        return true;
    }
    catch (const std::invalid_argument &e)
    {
        throw e;
    }
}

bool ThrowCard::validateCardHand(int indexCard, int maxIndex)
{
    if (indexCard > 0 && indexCard < maxIndex)
    {
        return true;
    }
    else
    {
        throw std::invalid_argument("Invalid index of Card from Hand");
    }
}