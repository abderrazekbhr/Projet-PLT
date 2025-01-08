#include "SetUpGame.h"
#include <stdexcept>
#include <vector>

namespace engine
{

    SetUpGame::SetUpGame(int nbPlayer, int maxScore, std::vector<std::string> &players, char playerIsIA, int level) : playersName(players)
    {

        this->setNewCMD(SETUP_GAME);
        this->nbPlayer = nbPlayer;
        this->maxScore = maxScore;
        this->playerIsIA = playerIsIA;
        this->level = level;
    }

    void SetUpGame::validateNbPlayer()
    {
        if (nbPlayer != 2 && nbPlayer != 4)
        {
            throw std::invalid_argument("The number of players must be 2 or 4.");
        }
    }

    void SetUpGame::validateMaxScore()
    {
        if (maxScore != 11 && maxScore != 21)
        {
            throw std::invalid_argument("The maximum score must be 11 or 21.");
        }
    }

    void SetUpGame::initPlayers(state::State &currentState)
    {
        int expectedPlayerNames = (playerIsIA == 'y' || playerIsIA == 'Y') ? nbPlayer - 1 : nbPlayer;

        if (playersName.size() != expectedPlayerNames)
        {
            throw std::invalid_argument("The number of players does not match the number of names provided.");
        }

        currentState.addPlayer(playersName.at(0));

        if (playerIsIA == 'y' || playerIsIA == 'Y') {
            currentState.addPlayer("AI");
        } else {
            for (int i = 1; i < nbPlayer; i++) {
                currentState.addPlayer(playersName.at(i));
            }
        }
    }


    bool SetUpGame::execute(Engine *engine)
    {
        try
        {
            validateNbPlayer();
            validateMaxScore();

            state::State &currentState = engine->getState();

            currentState.setNbPlayer(nbPlayer);
            currentState.setMaxScore(maxScore);

            initPlayers(currentState);

            return true;
        }
        catch (const std::invalid_argument &e)
        {

            throw e;
        }
    }
    SetUpGame::~SetUpGame() {}

}
