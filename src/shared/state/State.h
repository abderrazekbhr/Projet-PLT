// Generated by dia2code
#ifndef STATE__STATE__H
#define STATE__STATE__H

#include <vector>
#include <string>

namespace state {
  class Player;
  class GameBoard;
  class CardsDeck;
  class Observable;
}

#include "Observable.h"
#include "CardsDeck.h"
#include "GameBoard.h"
#include "Player.h"

namespace state {

  /// class State - 
  class State : public state::Observable {
    // Associations
    // Attributes
  public:
    int turn;
  private:
    std::vector<Player *> players;
    int nbPlayer;
    int maxScore;
    GameBoard* board;
    CardsDeck* allCards;
    int playerIndexForLastCapturedCard;
    // Operations
  public:
    State ();
    int getMaxScore ();
    int getNbPlayer ();
    GameBoard * getBoard ();
    void setNbPlayer (int newNbPlayer);
    void setMaxScore (int newMaxScore);
    void initCards ();
    CardsDeck * getAllCards ();
    int incrementTurn ();
    void initBoard ();
    void addPlayer (std::string namePlayer);
    std::vector<Player *> getAllPlayers ();
    void setPlayerIndexForLastCapturedCard (int newIndexPlayer);
    int getPlayerIndexForLastCapturedCard ();
    void addIA (std::string name, int level);
    ~State ();
    // Setters and Getters
  };

};

#endif
