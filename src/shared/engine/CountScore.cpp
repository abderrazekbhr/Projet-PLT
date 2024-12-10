#include "CountScore.h"
#include "engine.h"
#include "state/Card.h"
#include "state/Player.h"

namespace engine 
{
    CountScore::CountScore() {}

    CountScore::~CountScore() {}

    bool CountScore::execute(Engine* engine)
    {
        state::State& currentState = engine->getState();

        for(auto& player:currentState.getAllPlayers())
        {
            int numCards = player.getCollectCard().size();
            bool hasMaxCards = true;
            for (auto &otherPlayer : currentState.getAllPlayers()) {
                if (&otherPlayer != &player) 
                {
                    int otherNumCards = otherPlayer.getCollectCard().size();
                    if (otherNumCards > numCards) 
                    {
                    hasMaxCards = false;
                    break;
                    }
                }
            }
        if (hasMaxCards) {
        player.addToScore(1);
        }
    //*****************  Dinari Point : the one with the most diamonds cards
    //check if the current player has the most "Diamond" cards compared to all other players.
    //If no other player has more Diamond cards, the current player is awarded 1 point by calling addToScore(1).
        int numDiamonds = 0;
        for (state::Card &card : player.getCollectCard()) 
        {
            if (card.getTypeCard() == 2) {
                numDiamonds++;
            }
        }

        bool hasMaxDiamonds = true;

        for (auto &otherPlayer : currentState.getAllPlayers()) {
            if (&otherPlayer != &player) {
                int otherNumDiamonds = 0;
                for (state::Card &card : otherPlayer.getCollectCard()) 
                {
                    if (card.getTypeCard() == 2) {
                        otherNumDiamonds++;
                    }
                }
            if (otherNumDiamonds > numDiamonds) {
                hasMaxDiamonds = false;
                break;
            }
            }
        }

        if (hasMaxDiamonds) {
        player.addToScore(1);
        }
    //*********************** Barmila Point : the one with the most seven cards
    //checks if the current player has the most "Seven" cards compared to all other players.
    //If no other player has more Sevens, the current player is awarded 1 point by calling addToScore(1).
        int numSevens = 0;
        for (auto &card : player.getCollectCard()) {
            if (card.getNumberCard() == 7) {
                numSevens++;
        }
        }

        bool hasMaxSevens = true;

        for (auto &otherPlayer : currentState.getAllPlayers()) {
            if (&otherPlayer != &player) {

                int otherNumSevens = 0;
                for (auto &card : otherPlayer.getCollectCard()) {
                    if (card.getNumberCard() == 7) {
                        otherNumSevens++;
                }
            }
            if (otherNumSevens > numSevens) {
                hasMaxSevens = false;
                break;
            }
            }
        }

        if (hasMaxSevens) {
        player.addToScore(1);
        }
    //****************************** Saba hayya : the one with the seven diamonds
    //This code checks if the current player has a "Seven of Diamonds" card.
    //If the player has this specific card, they are awarded 1 point by calling addToScore(1).
        bool hasSevenOfDiamonds = false;
        for ( auto &card : player.getCollectCard()) {
            if (card.getNumberCard() == 7 && card.getTypeCard() == 2) {
                hasSevenOfDiamonds = true;
                break;
            }
        }
    if (hasSevenOfDiamonds) {
        player.addToScore(1);
    }

    }

    }


}
