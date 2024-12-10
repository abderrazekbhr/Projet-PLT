#include "Engine.h"

namespace engine
{
    Engine::Engine(){

        currentState =state::State();
    };

    Engine::~Engine(){};

    state::State& Engine::getState()
    {
        return currentState;
    }

    void Engine::init()
    {
        
    }

    void Engine::setNextPlayer()
    {

    }

    state::Player Engine::getActualPlayer(){
        return player.at();
    }

}