// Generated by dia2code
#ifndef ENGINE__THROWCARD__H
#define ENGINE__THROWCARD__H


namespace engine {
  class Engine;
  class Command;
}

#include "Command.h"

namespace engine {

  /// class ThrowCard - 
  class ThrowCard : public engine::Command {
    // Attributes
  public:
    int indexCardHand;
    // Operations
  public:
    ThrowCard (int indexCardHand);
    ~ThrowCard ();
    bool execute (Engine * engine);
  private:
    bool validateCardHand (int indexCard, int maxIndex);
    // Setters and Getters
  };

};

#endif
