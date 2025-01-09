#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>
#include "client.h"
#include "engine.h"

using namespace std;
using namespace client;
using namespace engine;

int main()
{
    cout << "Welcome to the game of CHKOBA!" << endl;

    // Initialize the client
    Client *c = new Client();
    c->setUp();

    // Game configuration
    int nbPlayer = c->getNbPlayerAndIA();
    int nbRound = 36 / nbPlayer; // Number of rounds based on total cards
    int nbTours = 3;             // Number of turns per round

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
                    cout << "--------------------------------------" << endl;
                    cout << "Turn of Player " << k + 1 << endl;

                    // Display player's hand and the board
                    cout << "CARDS IN YOUR HAND:" << endl;
                    c->displayHandCards();
                    cout << "CARDS ON THE BOARD:" << endl;
                    c->displayBoardCards();

                    // Let the player choose an action
                    if (c->chooseAction() == Throwing)
                    {
                        c->playThrowCard();
                    }
                    else
                    {
                        c->playCaptureCard();
                    }
                }
            }

            // End of round processing
            c->countScore(); // Calculate scores
            c->endRound();   // Handle end of round cards
            c->distributeCard(); // Distribute cards for the next round
        }

        // Ask if the user wants to continue playing
        cout << "Do you want to continue the game? (y/n)" << endl;
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
