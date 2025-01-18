#include "SetUpGame.h"

#include <iostream>
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
        if (maxScore != 4 && maxScore != 21)
        {
            throw std::invalid_argument("The maximum score must be 4 or 21.");
        }
    }

    void SetUpGame::initPlayers(state::State &currentState)
    {
        if (playerIsIA == 'y' || playerIsIA == 'Y')
        {
            for (int i = 0; i < nbPlayer; i++)
            {
                // Définir le niveau de l'IA en fonction du nom
                int aiLevel = 1;  // Par défaut, les IA Random sont au niveau 1
                if (playersName.at(i).find("HeuristicAI_2") != std::string::npos) {
                    aiLevel = 2; // Les IA Heuristic sont au niveau 2
                }

                // Vérifier les nouveaux noms des IA et les affecter en fonction de leur type
                if (playersName.at(i).find("RandomAI") != std::string::npos)
                {
                    currentState.addIA(playersName.at(i), aiLevel);
                }
                else if (playersName.at(i).find("HeuristicAI") != std::string::npos)
                {
                    currentState.addIA(playersName.at(i), aiLevel);
                }
                else
                {
                    // Ajout d'un joueur humain si le nom ne correspond à aucune IA
                    currentState.addPlayer(playersName.at(i));
                }
            }
        }
        else
        {
            // Ajouter le premier joueur comme humain, les autres comme IA ou humains
            currentState.addPlayer(playersName.at(0)); // Premier joueur toujours humain

            for (int i = 1; i < nbPlayer; i++)
            {
                if (playerIsIA == 'y' || playerIsIA == 'Y')
                {
                    currentState.addIA(playersName.at(i), level);
                }
                else
                {
                    currentState.addPlayer(playersName.at(i));
                }
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
            // Catch specific exception and rethrow if necessary
            throw e;
        }
    }

    SetUpGame::~SetUpGame() {}
}
