// Generated by dia2code
#ifndef ENGINE__COUNTSCORE__H
#define ENGINE__COUNTSCORE__H


namespace engine {
  class Engine;
};
namespace state {
  class Player;
  class State;
};
namespace engine {
  class Command;
}

#include "Command.h"

namespace engine {

  /// class CountScore - 
  class CountScore : public engine::Command {
    // Operations
  public:
    CountScore ();
    ~CountScore () override;
    bool execute (Engine * engine);
  private:
    bool hasMaxCards (state::Player& player, state::State & currentState);
    bool hasMaxDiamonds (state::Player& player, state::State & currentState);
    bool hasMaxSevens (state::Player& player, state::State & currentState);
    bool hasSevenOfDiamonds (state::Player& player);
    int countCardType (state::Player& player, int type);
    int countCardNumber (state::Player& player, int number);
    // Setters and Getters
  };

};

#endif
