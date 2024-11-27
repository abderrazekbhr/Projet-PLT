// Generated by dia2code
#ifndef STATE__GAME__H
#define STATE__GAME__H

#include <vector>

namespace state {
  class Player;
  class State;
  class Card;
  class GameBoard;
}

#include "Player.h"
#include "Card.h"
#include "GameBoard.h"

namespace state {

  /// class Game - 
  class Game {
    // Associations
    // Attributes
  private:
    static std::vector<Player> players;
    static GameBoard * board;
    State *  state;
    static int maxScore;
    static std::vector<Card> listOfCards;
    // Operations
  public:
    Game ();
    void setState (State * state);
    static int getMaxScore ();
    static void setMaxScore (int maxScore);
    void request ();
    static void CalculScorePlayer (Player & player);
    static void addPlayer (Player & player);
    static void addCard (Card & card);
    static void displayPlayers ();
    static GameBoard * getGameBoard ();
    static std::vector<Card> getListOfCards ();
    ~Game ();
    // Setters and Getters
  };

};

#endif
