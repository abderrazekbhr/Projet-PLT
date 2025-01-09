// Generated by dia2code
#ifndef STATE__PLAYER__H
#define STATE__PLAYER__H

#include <string>
#include <vector>

namespace state {
  class Card;
}

#include "Card.h"
#include "PlayerStatus.h"

namespace state {

  /// class Player - 
  class Player {
    // Attributes
  private:
    std::string name;
    int totalScore;
    std::vector<Card> collectedCard;
    std::vector<Card> holdedCard;
    PlayerStatus status;
    // Operations
  public:
    Player (std::string name);
    std::string getName ();
    void setName (std::string name);
    int getScore ();
    void addToScore (int score);
    std::vector<Card> getCollectCard ();
    void addCollectedCard (Card card);
    std::vector<Card> getHoldCard ();
    void addHoldCard (Card card);
    PlayerStatus getPlayerStatus ();
    void setPlayerStatus (PlayerStatus newStatus);
    Card selectCardFromHand (int cardIndex);
    void addHoldedCard (Card card);
    void removeCardFromHand (Card card);
    virtual ~Player ();
    int getSizeCollectedCards ();
    int getSizeHoldedCards ();
    // Setters and Getters
  };

};

#endif
