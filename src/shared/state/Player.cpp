#include <iostream>
#include <vector>
#include "state.h"

using namespace state;
using namespace std;    

Player::Player()
{
    this->name="Player " + to_string(rand());
    cout << "\n" << endl; 
}


int Player::getIdPlayer()
{
    return this->idPlayer;
}




