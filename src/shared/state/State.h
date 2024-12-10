// Generated by dia2code
#ifndef STATE__STATE__H
#define STATE__STATE__H

#include <vector>
<<<<<<< HEAD

=======
#include <string>
>>>>>>> df043d9d77211bd4375cc581b5bea3cdfe49e5bd

namespace state {
  class Player;
  class GameBoard;
  class CardsDeck;
}

#include "Player.h"
#include "GameBoard.h"
#include "CardsDeck.h"

namespace state {

  /// class State - 
  class State {
    // Associations
    // Attributes
  public:
    int turn;
  private:
    std::vector<Player> players;
    int nbPlayer;
    int maxScore;
    GameBoard board;
    CardsDeck allCards;
    // Operations
  public:
    State ();
    ~State ();
    void init ();
    void initPlayer (std::string name);
    int getMaxScore ();
    int getNbPlayer ();
    GameBoard getBoard ();
    void setNbPlayer (int newNbPlayer);
    void setMaxScore (int newMaxScore);
    void initCards ();
    void initBoard();
    CardsDeck getAllCards ();
    std::vector<Player> getAllPlayers();
    int incrementTurn ();
    // Setters and Getters
  };

};

#endif
