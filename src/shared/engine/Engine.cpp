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

    Command* Engine::getCurrentCommand() {
        return currentCmd;
    }

    void Engine::setCurrentCmd(Command* newCmd) {
        if (currentCmd != nullptr) {
            delete currentCmd;
        }
        currentCmd = newCmd;
    }

    Engine::~Engine() {};

}
