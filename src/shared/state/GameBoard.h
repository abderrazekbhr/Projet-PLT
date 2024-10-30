// Generated by dia2code
#ifndef STATE__GAMEBOARD__H
#define STATE__GAMEBOARD__H

#include <vector>

namespace state {
  class Card;
}

#include "Card.h"

namespace state {

  /// class GameBoard - 
  class GameBoard {
    // Associations
    // Attributes
  private:
    std::vector<Card> cardsOnBoard;
    // Operations
  public:
    GameBoard ();
    ~GameBoard ();
    int getNumberCardBoard ();
    void deleteCardFrom (Card card);
    void addCardToBoard (Card card);
    // Setters and Getters
  };

};

#endif
