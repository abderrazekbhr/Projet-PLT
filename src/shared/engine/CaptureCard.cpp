#include <iostream>
#include <vector>
#include "CaptureCard.h"

using namespace engine;
int indexCardHand;
std::vector<int> indexsCardsBoard;

CaptureCard::CaptureCard(int indexCardHand, std::vector<int> indexsCardFromBoard)
{
    this->setNewCMD(CAPTURE_CARD);
    this->indexCardHand = indexCardHand;
    this->indexsCardsBoard = indexsCardFromBoard;
}

bool CaptureCard::execute(Engine *engine)
{
    try
    {
        state::State currentState = engine->getState();
        state::Player player = engine->getActualPlayer();
        state::GameBoard *board = currentState.getBoard();
        this->validateCardHand(indexCardHand, player.getHoldCard().size()); // TODO: create a function to return the number of cards in the hand
        this->validateCardBoard(indexsCardsBoard, board->getNumberCardBoard());
        state::Card card = player.getHoldCard()[indexCardHand];
        player.removeCardFromHand(card);
        player.addCollectedCard(card);
        this->collectMultipleCard(*board, indexsCardsBoard, player);
        if (this->verifyChkoba(*board))
        {
            player.addToScore(1);
        }
        engine->setNextPlayer();
        return true;
    }
    catch (const std::invalid_argument &e)
    {
        throw e;
    }
}

bool CaptureCard::validateCardHand(int indexCard, int maxIndex)
{
    if (indexCard >= 0 && indexCard < maxIndex)
    {
        return true;
    }
    else
    {
        throw std::invalid_argument("Invalid index of Card from Hand");
    }
}
bool CaptureCard::validateCardBoard(std::vector<int> indexsCards, int maxIndex)
{
    int size = indexsCards.size();
    for (int i = 0; i < size; i++)
    {
        if (indexsCards[i] < 0 || indexsCards[i] >= maxIndex)
        {
            throw std::invalid_argument("Invalid index of Card from Board : index = " + indexsCards[i]);
        }
    }
    return true;
}
void CaptureCard::collectMultipleCard(state::GameBoard &board, std::vector<int> collectedCardIndexs, state::Player &player)
{
    int size = collectedCardIndexs.size();
    for (int i = 0; i < size; i++)
    {
        state::Card card = board.getCardBoard()[collectedCardIndexs[i]];
        player.addCollectedCard(card);
        board.removeCardBoard(card);
    }
}

bool CaptureCard::verifyChkoba(state::GameBoard board)
{
    if (board.getNumberCardBoard() == 0)
    {
        return true;
    }
    return false;
}

CaptureCard::~CaptureCard()
{
    indexsCardsBoard.clear();
}