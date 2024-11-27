// Generated by dia2code
#ifndef STATE__ENDGAMESTATE__H
#define STATE__ENDGAMESTATE__H

#include <vector>

namespace state {
  class Player;
  class State;
}

#include "Player.h"
#include "State.h"

namespace state {

  /// class EndGameState - 
  class EndGameState : public state::State {
    // Operations
  public:
    EndGameState ();
    ~EndGameState ();
    void handleRequest (std::vector<Player> & players);
    // Setters and Getters
  };

};

#endif
