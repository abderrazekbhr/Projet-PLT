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

    void Engine::init()
    {
        currentState.initCards();
        currentState.initBoard();
    }

    void Engine::setNextPlayer()
    {
        currentState.incrementTurn();
    }
    
    state::Player &Engine::getActualPlayer()
    {
        return *(currentState.getAllPlayers().at(currentState.turn));
    }

    Command* Engine::getCurrentCmd() {
        return currentCmd;
    }

    void Engine::setCurrentCmd(Command* newCmd) {
        currentCmd = newCmd;
    }

    Engine::~Engine() {};

}
