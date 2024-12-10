#include "SetUpGame.h"
#include <stdexcept>
#include <vector>


namespace engine {

    SetUpGame::SetUpGame(int nbPlayer, int maxScore,  std::vector<std::string>& playersNames)
        : nbPlayer(nbPlayer), maxScore(maxScore), playersNames(playersNames) {  // Initialisation des membres
    }

    SetUpGame::~SetUpGame() {}

    void SetUpGame::validateNbPlayer() {
        if (nbPlayer != 2 && nbPlayer != 4) {
            throw std::invalid_argument("The number of players must be 2 or 4.");
        }
    }

    void SetUpGame::validateMaxScore() {
        if (maxScore != 11 && maxScore != 21) {
            throw std::invalid_argument("The maximum score must be 11 or 21.");
        }
    }

    void SetUpGame::initPlayers(state::State& currentState) {
        if (playersNames.size() != nbPlayer) {
            throw std::invalid_argument("The number of players does not match the number of names provided.");
        }

        for (int i = 0; i < nbPlayer; i++) {
            currentState.addPlayer(playersNames.at(i));
        }
    }

    bool SetUpGame::execute(Engine* engine) {
        try {
            validateNbPlayer();
            validateMaxScore();


            state::State& currentState = engine->getState();

            currentState.setNbPlayer(nbPlayer);
            currentState.setMaxScore(maxScore);


            initPlayers(currentState);

            return true;
        } catch (const std::invalid_argument& e) {

            throw e;

        }
    }

}
