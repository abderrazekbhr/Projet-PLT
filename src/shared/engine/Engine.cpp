#include "Engine.h"
#include <stdexcept> // Nécessaire pour std::out_of_range
#include <iostream>
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
    bool Engine::runCommand(Engine *e)
    {
        if (actualCmd == nullptr)
        {
            std::cout << "No command to execute" << std::endl;
            return false;
        }
        return actualCmd->execute(e);
    }
    void Engine::setPlayerIndexForLastCapturedCard (){
        int index = currentState.turn;
        currentState.setPlayerIndexForLastCapturedCard(index);  
    }
    Engine::~Engine() {
        // delete &currentState;
    };

}
