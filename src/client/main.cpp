#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>
#include "client.h"
#include "engine.h"
#include "ai.h"

using namespace std;
using namespace client;
using namespace engine;
using namespace ai;

int main()
{
    cout << "Welcome to the game of CHKOBA!" << endl;

    // Initialize the client
    Client *c = new Client();
    c->setUp();

    // Game configuration
    int nbPlayer = c->getNbPlayerAndIA();
    int nbTours = 3; // Number of turns per round

    int nbRound = 36 / (nbPlayer * nbTours); // Number of rounds based on total cards

    // Main game loop
    while (!c->isEndOfGame())
    {
        // Distribute cards to players
        c->initDistribute();

        for (int i = 0; i < nbRound; i++) // Iterate through all rounds
        {
            for (int j = 0; j < nbTours; j++) // Iterate through all turns in a round
            {
                for (int k = 0; k < nbPlayer; k++) // Iterate through all players
                {
                    // Let the player choose an action
                    ActionType action = c->chooseAction(); // Call once and store result

                    if (action == Throwing)
                    {
                        c->playThrowCard();
                    }
                    else if (action == Collecting)
                    {
                        c->playCaptureCard();
                    }
                }
            }

            c->distributeCard(); // Distribute cards for the next round
        }

        // End of round processing
        c->endRound();   // Handle end of round cards
        c->countScore(); // Calculate scores

        // Check if the user wants to continue the game
        char response = c->getValidatedChar("Do you want to continue the game? (y/n): ");
        if (response == 'n' || response == 'N')
        {
            break; // Exit the game loop
        }
    }

    // Display the winner at the end of the game
    c->displayWinner();

    // Proper memory management
    delete c;

    return 0;
}
