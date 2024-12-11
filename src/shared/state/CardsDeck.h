// Generated by dia2code
#ifndef STATE__CARDSDECK__H
#define STATE__CARDSDECK__H

#include <vector>

namespace state {
  class Card;
  class Player;
  class GameBoard;
}

#include "Card.h"

namespace state {

  /// class CardsDeck - 
  class CardsDeck {
    // Associations
    // Attributes
  private:
    std::vector<Card> allCards;
    // Operations
  public:
    CardsDeck ();
    ~CardsDeck ();
    void distributeCards (std::vector<Player*> players, int nbCards);
    void distributeCardsOnBoard (GameBoard & board, int nbCards);
    void shuffleDeck ();
    int getDeckSize ();
    std::vector<Card> getAllCards ();
    // Setters and Getters
  };

};

#endif
