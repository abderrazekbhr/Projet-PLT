// Generated by dia2code
#ifndef STATE__PLAYER__H
#define STATE__PLAYER__H
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace state
{
  class Card;
}

#include "Card.h"

namespace state
{

  /// class Player -
  class Player
  {
    // Associations
    // Attributes
  private:
    int idPlayer;
    std::string name;
    int totalScore;
    std::vector<std::unique_ptr<Card>> collectedCard;
    std::vector<std::unique_ptr<Card>> holdedCard;
    // Operations
  public:
    Player();
    int getIdPlayer();
    std::string getName();
    void setName(std::string name);
    int getScore();
    ~Player();
    int getTotalCollectCard();
    int getTotalHoldCard();
    void dIsplayCollectCard();
    void displayHoldCard();
    // Setters and Getters
  };

};

#endif
