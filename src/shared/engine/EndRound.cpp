#include "EndRound.h"
#include <stdexcept>
#include <iostream>
#include "engine.h"
#include "state/State.h"

namespace engine {

    EndRound::EndRound() {}

    EndRound::~EndRound() {}

    bool EndRound::execute(Engine *engine) {
        try {
            state::State &currentState = engine->getState();

            // Vérification si le deck n'est pas vide
            if (currentState.getAllCards()->getDeckSize() != 0) {
                throw std::runtime_error("The deck is not empty. Cannot end the round.");
            }

            size_t lastCaptureIndex = currentState.getPlayerIndexForLastCapturedCard();
            std::vector<state::Player *> players = currentState.getAllPlayers();

            // Vérification si les joueurs ont encore des cartes en main
            for (const auto &player : players) {
                if (!player->getHoldCard().empty()) {
                    throw std::runtime_error("One or more players still have held cards. Cannot end the round.");
                }
            }

            // Vérification de la validité de l'index de la dernière capture
            if (lastCaptureIndex >= players.size()) {
                throw std::out_of_range("Invalid index for the last captured card.");
            }

            state::GameBoard *board = currentState.getBoard();

            // Vérification si le plateau est vide
            if (board->getNumberCardBoard() == 0) {
                return false;
            }

            // Transférer les cartes du plateau au joueur correspondant
            auto boardCards = board->getCardBoard();
            for (const auto &card : boardCards) {
                players[lastCaptureIndex]->addCollectedCard(card);
            }

            // Supprimer les cartes du plateau
            for (const auto &card : boardCards) {
                board->removeCardBoard(card);
            }

            return true;
        } catch (const std::exception &e) {
            std::cerr << "Error in EndRound::execute: " << e.what() << std::endl;
            return false;
        }
    }

}
