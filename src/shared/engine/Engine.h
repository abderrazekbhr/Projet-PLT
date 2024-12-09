// Generated by dia2code
#ifndef ENGINE__ENGINE__H
#define ENGINE__ENGINE__H


namespace state {
  class State;
  class Player;
}

#include "state/State.h"
#include "state/Player.h"

namespace engine {

  /// class Engine - 
  class Engine {
    // Attributes
  private:
    state::State currentState;
    // Operations
  public:
    Engine ();
    ~Engine ();
    void init ();
    state::State& getState ();
    void setNextPlayer ();
    state::Player& getActualPlayer ();
    // Setters and Getters
  };

};

#endif
