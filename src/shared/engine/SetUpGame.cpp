#include "SetUpGame.h"

namespace engine {

    SetUpGame::SetUpGame() {
        nbPlayer=0;
        maxScore=0;
    }
    SetUpGame::~SetUpGame() {}

    bool SetUpGame::execute (Engine* engine){

    state::State& currentState = engine->getState();
    currentState.setNbPlayer(nbPlayer);

    }

}