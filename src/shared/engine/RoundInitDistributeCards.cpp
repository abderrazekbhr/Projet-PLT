#include "RoundInitDistributeCards.h"
#include "state/Player.h"

namespace engine{

    RoundInitDistributeCards::RoundInitDistributeCards() {}
    RoundInitDistributeCards::~RoundInitDistributeCards() {}

    bool RoundInitDistributeCards::execute (Engine* engine){

        state::State& currentState = engine->getState();

        currentState.getAllCards().shuffleDeck();
    
            if (response == 'y' || response == 'Y') {
               
            currentState.getAllPlayers().at(0).addHoldCard();
       
       
        currentState.getAllCards().distributeCards(currentState.getAllPlayers(),2);

        for (int i = 0; i < 2; ++i) {
            mainPlayer.addHoldedCard(Game::getListOfCards().back());
            Game::getListOfCards().pop_back();
        }


        for (auto& player : state::players) {
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
        }else {
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
}