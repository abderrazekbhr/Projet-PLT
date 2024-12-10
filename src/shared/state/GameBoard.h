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
    // Attributes
  private:
    std::vector<Card> cardsOnBoard;
    // Operations
  public:
    GameBoard ();
    ~GameBoard ();
    std::vector<Card> getCardBoard();
    int getNumberCardBoard ();
    void addCardToBoard (Card card);
    void removeCardBoard (Card card);
    std::vector<Card> selectCardFromBoard (std::vector<int> cardIndexs);
    // Setters and Getters
  };

};

#endif
