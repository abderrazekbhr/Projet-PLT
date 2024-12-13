#include "Engine.h"

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

    Command * Engine::getActualCommand(){
        return actualCmd;
    }
    void Engine::setActualCmd(Command* newCmd) {
        actualCmd = newCmd;
    }

    Engine::~Engine() {};

}
