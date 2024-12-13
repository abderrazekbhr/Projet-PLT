#include "./ThrowCard.h"
#include "Command.h"
#include <stdexcept>
using namespace engine;

ThrowCard::ThrowCard(int indexCardHand)
{
    this->setNewCMD(
        THROW_CARD);
    this->indexCardHand = indexCardHand;
}
bool ThrowCard::execute(Engine *engine)
{
    state::Player player = engine->getActualPlayer();
    try
    {
        this->validateCardHand(indexCardHand, player.getHoldCard().size());
        engine->setNextPlayer();
        state::State currentState = engine->getState();
        state::Card card = player.getHoldCard()[indexCardHand];
        state::GameBoard *board = currentState.getBoard();
        player.removeCardFromHand(card);
        board->addCardToBoard(card);
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