#include "Engine.h"

namespace engine
{
    Engine::Engine()
    {

        currentState = state::State();
    };

    Engine::~Engine() {};

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

}
