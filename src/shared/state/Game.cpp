// #include <vector>
// #include "../state.h"
// #include "Game.h"
// #include <iostream>

// using namespace std;
// using namespace state;

// Game::Game() {
//     state = new WaitState();
//     board = new GameBoard();
//     // TODO :initCards()
//     for (int type = treffle; type <= coeur; ++type) {
//         for (int number = un; number <= roi; ++number) {
//             Card card(static_cast<NumberCard>(number), static_cast<TypeCard>(type));
//             addCard(card);
//         }
//     }

// }


// void Game::setState(State* state) {
//     delete this->state;
//     this->state = state;
// }

// void Game::request() {
//     this->state->handleRequest(players);
// }

// Game::~Game() {
//     delete state;

// }

// void Game::addPlayer(Player& player) {
//     players.push_back(player);
// }

// void Game::addCard(Card &card) {
//     listOfCards.push_back(card);
// }


// GameBoard * Game::getGameBoard() {
//     return board;
// }

// void Game::displayPlayers() {
//     cout << "Players are : "  << endl;
//     for (size_t i = 0; i < players.size(); ++i) {
//         cout << "Player " << i + 1 << ": " << players[i].getName() << endl;
//         players[i].displayHoldCard();
//         players[i].displayCollectCard();
//     }
// }

// int Game::getMaxScore() {
//     return maxScore;
// }

// void Game::setMaxScore(int maxScore) {
//     Game::maxScore = maxScore;
// }

// std::vector<Card> Game::getListOfCards() {
//     return listOfCards;
// }

// void Game::CalculScorePlayer(Player &player) {
//     //*************************************Karta Point: for the one with the most cards
// //check if the current player has the maximum number of cards compared to all other players.
// //If no other player has more cards, the current player is awarded 1 point by calling addToScore(1).
//     int numCards = player.getCollectCard().size();
//     bool hasMaxCards = true;
//     for (auto &otherPlayer : players) {
//         if (&otherPlayer != &player) {
//             int otherNumCards = otherPlayer.getCollectCard().size();
//             if (otherNumCards > numCards) {
//                 hasMaxCards = false;
//                 break;
//             }
//         }
//     }
//     if (hasMaxCards) {
//         player.addToScore(1);
//     }
// //*****************  Dinari Point : the one with the most diamonds cards
// //check if the current player has the most "Diamond" cards compared to all other players.
// //If no other player has more Diamond cards, the current player is awarded 1 point by calling addToScore(1).
//     int numDiamonds = 0;
//     for (Card &card : player.getCollectCard()) {
//         if (card.getTypeCard() == carreau) {
//             numDiamonds++;
//         }
//     }

//     bool hasMaxDiamonds = true;

//     for (auto &otherPlayer : players) {
//         if (&otherPlayer != &player) {
//             int otherNumDiamonds = 0;
//             for (Card &card : otherPlayer.getCollectCard()) {
//                 if (card.getTypeCard() == carreau) {
//                     otherNumDiamonds++;
//                 }
//             }
//             if (otherNumDiamonds > numDiamonds) {
//                 hasMaxDiamonds = false;
//                 break;
//             }
//         }
//     }

//     if (hasMaxDiamonds) {
//         player.addToScore(1);
//     }
//     //*********************** Barmila Point : the one with the most seven cards
// //checks if the current player has the most "Seven" cards compared to all other players.
// //If no other player has more Sevens, the current player is awarded 1 point by calling addToScore(1).
//     int numSevens = 0;
//     for (auto &card : player.getCollectCard()) {
//         if (card.getNumberCard() == sept) {
//             numSevens++;
//         }
//     }

//     bool hasMaxSevens = true;

//     for (auto &otherPlayer : players) {
//         if (&otherPlayer != &player) {

//             int otherNumSevens = 0;
//             for (auto &card : otherPlayer.getCollectCard()) {
//                 if (card.getNumberCard() == sept) {
//                     otherNumSevens++;
//                 }
//             }
//             if (otherNumSevens > numSevens) {
//                 hasMaxSevens = false;
//                 break;
//             }
//         }
//     }

//     if (hasMaxSevens) {
//         player.addToScore(1);
//     }
// //****************************** Saba hayya : the one with the seven diamonds
// //This code checks if the current player has a "Seven of Diamonds" card.
// //If the player has this specific card, they are awarded 1 point by calling addToScore(1).
//     bool hasSevenOfDiamonds = false;
//     for ( auto &card : player.getCollectCard()) {
//         if (card.getNumberCard() == sept && card.getTypeCard() == carreau) {
//             hasSevenOfDiamonds = true;
//             break;
//         }
//     }
//     if (hasSevenOfDiamonds) {
//         player.addToScore(1);
//     }



<<<<<<< HEAD
}

int numCards = player.getCollectCard().size();
            bool hasMaxCards = true;
            for (auto &otherPlayer : currentState.getAllPlayers()) 
            {
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
            if (hasMaxCards) 
            {
            player.addToScore(1);
            }
            //*****************  Dinari Point : the one with the most diamonds cards
            //check if the current player has the most "Diamond" cards compared to all other players.
            //If no other player has more Diamond cards, the current player is awarded 1 point by calling addToScore(1).
            int numDiamonds = 0;
            for (Card &card : player.getCollectCard()) 
            {
            if (card.getTypeCard() == carreau) 
                {
                    numDiamonds++;
                }
            }

            bool hasMaxDiamonds = true;

            for (auto &otherPlayer : players) {
            if (&otherPlayer != &player) {
                int otherNumDiamonds = 0;
                for (Card &card : otherPlayer.getCollectCard()) {
                    if (card.getTypeCard() == carreau) {
                        otherNumDiamonds++;
                    }
                }
                if (otherNumDiamonds > numDiamonds) {
                    hasMaxDiamonds = false;
                    break;
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
            if (card.getNumberCard() == sept) {
                numSevens++;
            }

            bool hasMaxSevens = true;

            for (auto &otherPlayer : players) {
            if (&otherPlayer != &player) {

                int otherNumSevens = 0;
                for (auto &card : otherPlayer.getCollectCard()) {
                    if (card.getNumberCard() == sept) {
                        otherNumSevens++;
                    }
                }
                if (otherNumSevens > numSevens) {
                    hasMaxSevens = false;
                    break;
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
            if (card.getNumberCard() == sept && card.getTypeCard() == carreau) {
                hasSevenOfDiamonds = true;
                break;
            }
            }
            if (hasSevenOfDiamonds) {
            player.addToScore(1);
            }
=======
// }
>>>>>>> df043d9d77211bd4375cc581b5bea3cdfe49e5bd
