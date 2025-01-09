#include "EndRound.h"
#include <stdexcept>
#include <iostream>

#include "engine.h"
#include "state/State.h"

namespace engine
{

    EndRound::EndRound() {}

    EndRound::~EndRound() {}

    bool EndRound::execute(Engine *engine)
    {
        try
        {
            state::State &currentState = engine->getState();
            std::cout<<"nbCards:"<<currentState.getAllCards()->getDeckSize()<<std::endl;
            if (currentState.getAllCards()->getDeckSize() != 0)
            {
                throw std::runtime_error("The deck is not empty. Cannot end the round.");
            }

            size_t lastCaptureIndex = currentState.getPlayerIndexForLastCapturedCard();
            std::vector<state::Player *> players = currentState.getAllPlayers();

            if (lastCaptureIndex >= players.size())
            {
                throw std::out_of_range("Invalid index for the last captured card.");
            }

            state::GameBoard *board = currentState.getBoard();

            if (board->getNumberCardBoard() == 0)
            {
                return false;
            }

            auto boardCards = board->getCardBoard();

            for (const auto &card : boardCards)
            {
                players[lastCaptureIndex]->addCollectedCard(card);
            }

            for (const auto &card : boardCards)
            {
                board->removeCardBoard(card);
            }

            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error in EndRound::execute: " << e.what() << std::endl;
            return false;
        }
    }

}
