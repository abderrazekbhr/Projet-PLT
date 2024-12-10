#ifndef ENGINE__COUNTSCORE__H
#define ENGINE__COUNTSCORE__H

namespace engine {
  class Engine;
  class Command;
}

#include "Command.h"
#include "state/Player.h"  // Inclure l'en-tête pour Player et State si nécessaire
#include "state/Card.h"

namespace engine {

  /// class CountScore - This class manages the score counting for the players based on the game rules.
  class CountScore : public engine::Command {
    // Operations
  private:
    bool hasMaxCards(state::Player& player, state::State& currentState);
    bool hasMaxDiamonds(state::Player& player, state::State& currentState);
    bool hasMaxSevens(state::Player& player, state::State& currentState);
    bool hasSevenOfDiamonds(state::Player& player);

    // Utility methods for counting specific types or numbers of cards
    int countCardType(state::Player& player, int type); // Count cards of a specific type
    int countCardNumber(state::Player& player, int number); // Count cards of a specific number


  public:
    CountScore (); // Constructor
    ~CountScore (); // Destructor

    bool execute (Engine * engine); // Main execution function to count and assign scores

    // Specific methods for checking if a player has the most cards based on various criteria



  };

};

#endif
