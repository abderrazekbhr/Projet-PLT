#include "Engine.h"
#include <iostream>
namespace engine
{
    Engine::Engine()
    {
        currentState = state::State();

    };

    state::State &Engine::getState()
    {
        return currentState;
    }



    void Engine::setNextPlayer()
    {
        currentState.incrementTurn();
    }

    state::Player &Engine::getActualPlayer()
    {
        return *(currentState.getAllPlayers().at(currentState.turn));
    }

    Engine::~Engine() {

    }


}


