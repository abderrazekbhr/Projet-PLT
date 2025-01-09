#include "./ThrowCard.h"
#include "Command.h"
#include <stdexcept>
#include <iostream>
using namespace std;
using namespace engine;

ThrowCard::ThrowCard(int indexCardHand)
{
    this->setNewCMD(THROW_CARD);
    this->indexCardHand = indexCardHand;
}
bool ThrowCard::execute(Engine *engine)
{
    try
    {
        state::Player& player = engine->getActualPlayer();
        this->validateCardHand(indexCardHand, player.getHoldCard().size());
        engine->setNextPlayer();

        state::State currentState = engine->getState();
        state::Card card = player.getHoldCard()[indexCardHand];
        state::GameBoard *board = currentState.getBoard();

        player.removeCardFromHand(card);
        board->addCardToBoard(card);
        std::cout << "Card added to board" << std::endl;
        return true;
    }
    catch (std::exception &e) // Catch all exceptions
    {
        return false;
    }
}

bool ThrowCard::validateCardHand(int indexCard, int maxIndex)
{
    if (indexCard >= 0 && indexCard < maxIndex)
    {
        return true;
    }
    else
    {
        throw std::out_of_range("Invalid index of Card from Hand");
    }
}

ThrowCard::~ThrowCard (){}