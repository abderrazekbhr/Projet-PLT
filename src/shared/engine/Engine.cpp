#include "Engine.h"
#include <stdexcept> // Nécessaire pour std::out_of_range

#include "Command.h"

namespace engine
{
    Engine::Engine()
    {
        currentState = state::State();
        actualCmd = nullptr;
    };

    void Engine::setNextPlayer()
    {
        currentState.incrementTurn();
    }

    state::State &Engine::getState()
    {

        return currentState;
    }

    state::Player &Engine::getActualPlayer()
    {

        if (currentState.turn >= static_cast<int>(currentState.getAllPlayers().size()))
        {

            throw std::out_of_range("Turn index out of bounds in getActualPlayer");
        }
        return *(currentState.getAllPlayers().at(currentState.turn));
    }

    Command *Engine::getActualCommand()
    {
        return actualCmd;
    }

    void Engine::setActualCmd(Command *newCmd)
    {
        actualCmd = newCmd;
    }

    Engine::~Engine() {
        // delete &currentState;
    };
    void Engine::runCommand() {
        actualCmd->execute(this);
    }


}
