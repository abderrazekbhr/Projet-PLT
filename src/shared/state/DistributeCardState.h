// Generated by dia2code
#ifndef STATE__DISTRIBUTECARDSTATE__H
#define STATE__DISTRIBUTECARDSTATE__H

#include <vector>

namespace state {
  class Player;
  class State;
}

#include "Player.h"
#include "State.h"

namespace state {

  /// class DistributeCardState - 
  class DistributeCardState : public state::State {
    // Operations
  public:
    DistributeCardState ();
    ~DistributeCardState ();
    void handleRequest (std::vector<Player> & players);
    // Setters and Getters
  };

};

#endif
