#include "../state.h"
#include "Game.h"
#include "GameBoard.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

using namespace state;

InitState::InitState() {
    std::cout << "InitState initialized..." << std::endl;
}

InitState::~InitState() {
    std::cout << "InitState destroyed..." << std::endl;
}

void InitState::handleRequest(std::vector<Player>& players) {
    //it must be verified that at least one player is waiting before the game can be initiated
    if (players.size() != 1) {
        std::cerr << "Error: We must have one player at this state." << std::endl;
        return;
    }

    Player& mainPlayer = players[0];
    int choice;

//the main player will choose the game mode, either for 2 players or 4 players
    while (true) {
        std::cout << mainPlayer.getName() << ", Choose the number of players (2 or 4): ";
        std::cin >> choice;

        if (choice == 2 || choice == 4) {
            for (int i = 1; i < choice; i++) {
                Player* newPlayer = new Player();
                Game::addPlayer(*newPlayer);
            }
            break;
        }
        std::cerr << "Invalid choice. You must choose 2 or 4." << std::endl;
    }

//the main player will also choose the final score to reach either 11 or 21
    int scoreChoice;
    while (true) {
        std::cout << mainPlayer.getName() << ", Choose the final score for the game (11 or 21): ";
        std::cin >> scoreChoice;

        if (scoreChoice == 11 || scoreChoice == 21) {
            Game::setMaxScore(scoreChoice);
            std::cout << "Final score set to " << scoreChoice << "." << std::endl;
            break;
        }
        std::cerr << "Invalid choice. You must choose 11 or 21." << std::endl;
    }

// we shuffle the cards and the main player will take the first card and he has the option to keep the card or not
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(Game::getListOfCards().begin(), Game::getListOfCards().end(), std::default_random_engine(seed));

    Card firstCard = Game::getListOfCards().back();
    Game::getListOfCards().pop_back();

    char response;
    std::cout << mainPlayer.getName() << ", you received a card. Do you want to keep it? (y/n): ";
    std::cin >> response;
//if he keeps the card, he will receive 2 additional cards bases on the one he kept,
//then, 3 cards will be received to the others players and 4 cards will be placed on the board
    if (response == 'y' || response == 'Y') {
        mainPlayer.addHoldedCard(firstCard);
        // std::cout << "You kept the card." << std::endl;


        for (int i = 0; i < 2; ++i) {
            mainPlayer.addHoldedCard(Game::getListOfCards().back());
            Game::getListOfCards().pop_back();
        }


        for (auto& player : players) {
            if (&player != &mainPlayer) {
                for (int i = 0; i < 3; ++i) {
                    player.addHoldedCard(Game::getListOfCards().back());
                    Game::getListOfCards().pop_back();
                }
            }
        }


        for (int i = 0; i < 4; ++i) {
            Game::getGameBoard()->addCardToBoard(Game::getListOfCards().back());
            Game::getListOfCards().pop_back();
        }
    } else {
// if he doesn't keep the card, it will be placed on the board
        //THen, 3 more cards will be added to the board and 3 cards will be dealt to each player
        Game::getGameBoard()->addCardToBoard(firstCard);
        // std::cout << "You placed the card on the board." << std::endl;


        for (int i = 0; i < 3; ++i) {
            Game::getGameBoard()->addCardToBoard(Game::getListOfCards().back());
            Game::getListOfCards().pop_back();
        }


        for (auto& player : players) {

                for (int i = 0; i < 3; ++i) {
                    player.addHoldedCard(Game::getListOfCards().back());
                    Game::getListOfCards().pop_back();
                }

        }
    }

    // std::cout << "Card distribution completed." << std::endl;
}
