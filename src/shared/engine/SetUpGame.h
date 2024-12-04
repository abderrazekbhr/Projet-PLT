// Generated by dia2code
#ifndef ENGINE__SETUPGAME__H
#define ENGINE__SETUPGAME__H

#include <string>
#include <vector>

namespace engine {
  class Engine;
  class Command;
}

#include "Command.h"

namespace engine {

  /// class SetUpGame - 
class SetUpGame : public engine::Command {
    private:
    int nbPlayer; 
    int maxScore;
    // Operations
  public:
    SetUpGame ();
    ~SetUpGame ();
    bool execute (Engine* engine);
    // Setters and Getters
  };

};

#endif
