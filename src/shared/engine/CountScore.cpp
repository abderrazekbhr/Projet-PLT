#include "CountScore.h"
#include "engine.h"
#include "state/Card.h"
#include "state/Player.h"

namespace engine {

    CountScore::CountScore() {}

    CountScore::~CountScore() {}

    // Main execution function to count and assign scores based on the player's collected cards
    bool CountScore::execute(Engine* engine)
    {
        state::State& currentState = engine->getState();

        // Loop through all players to assign points based on the game rules
        for (auto& player : currentState.getAllPlayers()) {
            // Award points if the player has the most cards
            if (hasMaxCards(player, currentState)) {
                player.addToScore(1);
            }

            // Award points if the player has the most "Diamond" cards
            if (hasMaxDiamonds(player, currentState)) {
                player.addToScore(1);
            }

            // Award points if the player has the most "Seven" cards
            if (hasMaxSevens(player, currentState)) {
                player.addToScore(1);
            }

            // Award points if the player has a "Seven of Diamonds"
            if (hasSevenOfDiamonds(player)) {
                player.addToScore(1);
            }
        }

        return true;
    }

    // Check if a player has the maximum number of cards compared to all other players
    bool CountScore::hasMaxCards(state::Player& player, state::State& currentState) {
        int numCards = player.getSizeCollectedCards();

        // Loop through all other players to check if any player has more cards
        for (auto& otherPlayer : currentState.getAllPlayers()) {
            bool isNotSamePlayer = &otherPlayer != &player;  // Check if the player is different
            bool hasMoreCards = otherPlayer.getSizeCollectedCards() > numCards;  // Check if other player has more cards

            // If any player has more cards, return false
            if (isNotSamePlayer && hasMoreCards) {
                return false;
            }
        }

        return true; // Player has the most cards
    }

    // Check if a player has the most "Diamond" cards (Diamond is type 2)
    bool CountScore::hasMaxDiamonds(state::Player& player, state::State& currentState) {
        int numDiamonds = countCardType(player, 2);  // Count number of "Diamond" cards for this player

        // Loop through all other players to check if any player has more Diamond cards
        for (auto& otherPlayer : currentState.getAllPlayers()) {
            bool isNotSamePlayer = &otherPlayer != &player;  // Check if it's not the same player
            bool hasMoreDiamonds = countCardType(otherPlayer, 2) > numDiamonds;  // Check if the other player has more Diamonds

            if (isNotSamePlayer && hasMoreDiamonds) {
                return false;  // If another player has more Diamond cards, return false
            }
        }
        return true;  // Player has the most Diamond cards
    }

    // Check if a player has the most "Seven" cards
    bool CountScore::hasMaxSevens(state::Player& player, state::State& currentState) {
        int numSevens = countCardNumber(player, 7);  // Count number of "Seven" cards for this player

        // Loop through all other players to check if any player has more Seven cards
        for (auto& otherPlayer : currentState.getAllPlayers()) {
            bool isNotSamePlayer = &otherPlayer != &player;  // Check if it's not the same player
            bool hasMoreSevens = countCardNumber(otherPlayer, 7) > numSevens;  // Check if the other player has more Sevens

            if (isNotSamePlayer && hasMoreSevens) {
                return false;  // If another player has more Seven cards, return false
            }
        }
        return true;  // Player has the most Seven cards
    }


    // Check if a player has the "Seven of Diamonds" card
    bool CountScore::hasSevenOfDiamonds(state::Player& player) {
        // Loop through all cards to check if the player has a "Seven of Diamonds"
        for (auto& card : player.getCollectCard()) {
            if (card.getNumberCard() == 7 && card.getTypeCard() == 2) {
                return true;  // Player has the "Seven of Diamonds" card
            }
        }
        return false; // Player does not have the "Seven of Diamonds"
    }

    // Utility function to count the number of cards of a specific type (e.g., Diamonds)
    int CountScore::countCardType(state::Player& player, int type) {
        int count = 0;

        // Count the number of cards of the given type
        for (auto& card : player.getCollectCard()) {
            if (card.getTypeCard() == type) {
                count++;
            }
        }

        return count;
    }

    // Utility function to count the number of cards with a specific number (e.g., Sevens)
    int CountScore::countCardNumber(state::Player& player, int number) {
        int count = 0;

        // Count the number of cards with the given number
        for (auto& card : player.getCollectCard()) {
            if (card.getNumberCard() == number) {
                count++;
            }
        }

        return count;
    }

}
