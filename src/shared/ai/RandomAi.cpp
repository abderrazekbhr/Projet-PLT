#include "RandomAi.h"
#include "../engine/CaptureCard.h"
#include "../engine/ThrowCard.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace ai;
using namespace engine;
using namespace state;

namespace ai {

RandomAi::RandomAi() {
    std::srand((unsigned int)std::time(0));
}

RandomAi::~RandomAi() {}

void RandomAi::run(engine::Engine eng) {
    state::State& currentState = eng.getState();
    state::Player& player = eng.getActualPlayer();
    state::GameBoard* board = currentState.getBoard();

    if (!board || player.getSizeHoldedCards() == 0) {
        return;
    }

    std::vector<state::Card> handCards = player.getHoldCard();
    std::vector<state::Card> boardCards = board->getCardBoard();

    // Logs avant l'exécution
    std::cout << "Cartes dans la main avant : " << player.getSizeHoldedCards() << "\n";
    for (size_t i = 0; i < handCards.size(); i++) {
        std::cout << "  Carte dans la main [" << i << "] : ("
                  << handCards[i].getNumberCard() << ", "
                  << handCards[i].getTypeCard() << ")\n";
    }

    std::cout << "Cartes capturées avant : " << player.getSizeCollectedCards() << "\n";

    std::cout << "Cartes sur le plateau avant : " << boardCards.size() << "\n";
    for (size_t i = 0; i < boardCards.size(); i++) {
        std::cout << "  Carte sur le plateau [" << i << "] : ("
                  << boardCards[i].getNumberCard() << ", "
                  << boardCards[i].getTypeCard() << ")\n";
    }

    // Logique de l'IA
    for (size_t i = 0; i < handCards.size(); i++) {
        for (size_t j = 0; j < boardCards.size(); j++) {
            if (handCards[i].equals(boardCards[j])) {
                CaptureCard captureAction(static_cast<int>(i), {static_cast<int>(j)});

                if (captureAction.execute(&eng)) {
                    // Logs après capture
                    std::cout << "Action : CaptureCard exécutée avec succès.\n";
                    std::cout << "Carte capturée : ("
                              << handCards[i].getNumberCard() << ", "
                              << handCards[i].getTypeCard() << ")\n";
                    std::cout << "Cartes dans la main après : " << player.getSizeHoldedCards() << "\n";
                    std::cout << "Cartes capturées après : " << player.getSizeCollectedCards() << "\n";
                    return;
                }
            }
        }
    }

    // Si aucune capture n'est possible, lancer une carte
    size_t randomIndex = std::rand() % handCards.size();
    ThrowCard throwAction(randomIndex);
    throwAction.execute(&eng);

    // Logs après avoir lancé une carte
    std::cout << "Action : ThrowCard exécutée avec succès.\n";
    std::cout << "Carte lancée : ("
              << handCards[randomIndex].getNumberCard() << ", "
              << handCards[randomIndex].getTypeCard() << ")\n";
    std::cout << "Cartes dans la main après : " << player.getSizeHoldedCards() << "\n";
    std::cout << "Cartes capturées après : " << player.getSizeCollectedCards() << "\n";
    std::cout << "Cartes sur le plateau après : " << boardCards.size() << "\n";
}

} // namespace ai
