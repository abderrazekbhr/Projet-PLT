#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}
// end of test SFML

#include "../shared/state.h"

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    Example example;
    example.setX(53);

    cout << "Bonjour tout le monde on va faire un jeu de carte !" << endl;

    return 0;
}
