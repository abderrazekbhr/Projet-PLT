#include <iostream>
#include <vector>
#include "CaptureCard.h"

using namespace engine;

CaptureCard::CaptureCard(int indexCardHand, std::vector<int> indexsCardFromBoard)
{
    this->setNewCMD(CAPTURE_CARD);
    this->indexCardHand = indexCardHand;
    this->indexsCardsBoard = std::move(indexsCardFromBoard); // Use move to avoid unnecessary copying
}

bool CaptureCard::execute(Engine *engine)
{
    try
    {
        // Get the current state and player
        state::State &currentState = engine->getState();
        state::Player &player = engine->getActualPlayer();
        state::GameBoard *board = currentState.getBoard();

        // Ensure board is not null
        if (!board)
        {
            throw std::runtime_error("GameBoard pointer is null");
        }

        // Validate indices before performing any operation
        this->validateCardHand(indexCardHand, player.getSizeHoldedCards());
        this->validateCardBoard(indexsCardsBoard, board->getNumberCardBoard());

        // Capture card from hand
        state::Card card = player.getHoldCard()[indexCardHand];
        std::vector<state::Card> cardBoard;
        for (int index : indexsCardsBoard)
        {
            cardBoard.push_back(board->getCardBoard()[index]);
        }

        if (!validateSum(card, cardBoard))
        {
            return false;
        }

        player.removeCardFromHand(card);
        player.addCollectedCard(card);

        // Capture cards from board
        this->collectMultipleCard(*board, cardBoard, player);

        // Check chkoba condition
        if (this->verifyChkoba(*board))
        {
            player.addToScore(1);
        }
        engine->setPlayerIndexForLastCapturedCard();
        // Update to next player
        engine->setNextPlayer();
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception in execute: " << e.what() << std::endl;
        return false;
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
        throw std::out_of_range("Invalid index of Card from Hand");
    }
}

bool CaptureCard::validateCardBoard(std::vector<int> indexsCards, int maxIndex)
{

    for (int index : indexsCards)
    {
        if (index < 0 || index >= maxIndex)
        {
            throw std::out_of_range("Invalid index of Card from Board");
        }
    }
    return true;
}

bool CaptureCard::validateSum(state::Card cardFromHand, std::vector<state::Card> cardBoard)
{
    int sum = 0;
    for (auto &card : cardBoard) // Use const reference to avoid unnecessary copies
    {
        sum += card.getNumberCard();
    }
    return sum == cardFromHand.getNumberCard();
}

void CaptureCard::collectMultipleCard(state::GameBoard &board, std::vector<state::Card> cardToCollectedFromBoard, state::Player &player)
{
    for (const state::Card &card : cardToCollectedFromBoard)
    {
        player.addCollectedCard(card);
        board.removeCardBoard(card);
    }
}

bool CaptureCard::verifyChkoba(state::GameBoard board)
{
    return board.getNumberCardBoard() == 0;
}

CaptureCard::~CaptureCard()
{
    // The vector clears automatically in the destructor
    indexsCardsBoard.clear();
}
