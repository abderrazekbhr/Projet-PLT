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
    Client *c = new Client();

    c->setUp();

    int nbPlayer = c->getNbPlayerAndIA();
    int nbRound = 36 / nbPlayer;
    int nbTours = 3;
    while (!c->isEndOfGame())
    {
        c->initDistribute();

        for (int i = 0; i < nbRound; i++)
        {
            for (int j = 0; i < nbTours; j++)
            {
                for (int k = 0; k < nbPlayer; k++)
                {
                    cout << "--------------------------------------" << endl;
                    cout << "Tour of player" << k + 1 << endl;
                    // c->displayCards(c->engine.getState().getAllPlayers()[k]->getHoldCard());
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
            c->distributeCard();
        }
        cout << "do you want to continue the game ? (y/n)" << endl;
        char response = c->getValidatedChar("Do you want to continue the game ? (y/n): ");
        if (response == 'n' || response == 'N')
        {
            break;
        }
    }
    return 0;
}
