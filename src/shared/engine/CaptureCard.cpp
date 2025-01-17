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
        // Obtenez l'état actuel et le joueur
        state::State &currentState = engine->getState();
        state::Player &player = engine->getActualPlayer();
        state::GameBoard *board = currentState.getBoard();
        std::vector<state::Card> cardsOnBoard = board->getCardBoard();
        std::vector<state::Card> cardsToCollect;

        // Validez les indices
        this->validateCardHand(indexCardHand, player.getSizeHoldedCards());
        this->validateCardBoard(indexsCardsBoard, board->getNumberCardBoard());

        // Carte de la main du joueur
        state::Card cardFromHand = player.getHoldCard()[indexCardHand];

        // Vérifiez pour un match direct
        bool directMatchFound = false;
        int directMatchIndex = -1;

        for (size_t i = 0; i < cardsOnBoard.size(); ++i)
        {
            if (cardsOnBoard[i].getNumberCard() == cardFromHand.getNumberCard())
            {
                directMatchFound = true;
                // directMatchIndex = static_cast<int>(i);
                break;
            }
        }

        if (directMatchFound)
        {
            // Si un match direct existe, vérifiez les indices
            if (indexsCardsBoard.size() != 1 || !cardsOnBoard[indexsCardsBoard[0]].getNumberCard() == cardFromHand.getNumberCard())
            {
                std::cout << "Invalid indices for direct match." << std::endl;
                return false;
            }

            cardsToCollect.push_back(cardsOnBoard[indexsCardsBoard[0]]);
        }
        else
        {
            // Validez les cartes sélectionnées pour la somme
            for (int index : indexsCardsBoard)
            {
                cardsToCollect.push_back(cardsOnBoard[index]);
            }

            if (!validateSum(cardFromHand, cardsToCollect))
            {
                std::cout << "Invalid sum." << std::endl;
                return false; // Somme invalide
            }
        }

        // Capture des cartes
        player.removeCardFromHand(cardFromHand);
        player.addCollectedCard(cardFromHand);

        // Capture multiple cartes depuis le plateau
        this->collectMultipleCard(*board, cardsToCollect, player);

        // Vérifiez la condition "chkoba"
        if (this->verifyChkoba(*board))
        {
            player.addToScore(1);
        }

        // Mettez à jour l'état de l'engin
        engine->setPlayerIndexForLastCapturedCard();
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
