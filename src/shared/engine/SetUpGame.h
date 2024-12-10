// Generated by dia2code
#ifndef ENGINE__SETUPGAME__H
#define ENGINE__SETUPGAME__H

#include <string>
#include <vector>

namespace engine {
  class Engine;
};
namespace state {
  class State;
};
namespace engine {
  class Command;
}

#include "Command.h"

namespace engine {

  /// class SetUpGame - 
  class SetUpGame : public engine::Command {
    // Attributes
  public:
    std::vector<std::string>& playersName;
  private:
    int nbPlayer;
    int maxScore;
    // Operations
  public:
    SetUpGame (int nbPlayer, int maxScore, std::vector<std::string>& players);
    bool execute (Engine* engine);
    ~SetUpGame ();
  private:
    void validateNbPlayer ();
    void validateMaxScore ();
    void initPlayers (state::State & currentState);
    // Setters and Getters
  };

};

#endif
