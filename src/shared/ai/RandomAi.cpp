#include "RandomAi.h"
#include "../engine/CaptureCard.h"
#include "../engine/ThrowCard.h"
#include <cstdlib> 
#include <ctime>

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

    for (int i = 0; i < handCards.size(); i++) {
        for (int j = 0; j < boardCards.size(); j++) {
            if (handCards[i].equals(boardCards[j])) {

                CaptureCard captureAction(i, {j});

                if (captureAction.execute(&eng)) {
                    return; 
                }
            }
        }
    }

    int randomIndex = std::rand() % handCards.size();
    ThrowCard throwAction(randomIndex);
    throwAction.execute(&eng);
}

} 
