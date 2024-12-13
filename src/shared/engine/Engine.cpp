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

<<<<<<< HEAD
    Command * Engine::getActualCommand(){
        return actualCmd;
    }
    void Engine::setActualCmd(Command* newCmd) {
        actualCmd = newCmd;
    }

    Engine::~Engine() {};
=======
    Engine::~Engine() {

    }

>>>>>>> 5eae01bb4ecc8428310bbb3cbd3446161ed05c1b

}


