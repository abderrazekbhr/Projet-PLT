#define BOOST_TEST_MODULE ThrowCard
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "state.h"
#include "engine.h"

using namespace state;
using namespace engine;
using namespace std;
BOOST_AUTO_TEST_SUITE(ThrowCard)

// test execute method
BOOST_AUTO_TEST_CASE(all_throwCard_tests)
{
    // Preparing new state
    Engine *e = new Engine();
    e->init();
    State s1 = e->getState();
    int nbPlayer = 2;
    int maxScore = 11;
    s1.setNbPlayer(nbPlayer);
    s1.setMaxScore(maxScore);
    s1.initBoard();
    s1.initCards();
    for (int i = 0; i < s1.getNbPlayer(); i++)
    {
        s1.addPlayer("User" + (i + 1));
    }
    vector<Player*> players=s1.getAllPlayers();
    NumberCard numbersCardOfCards[]={un,deux,trois};
    NumberCard numbersCardOfCards[]={un,deux,trois};


    
}
BOOST_AUTO_TEST_SUITE_END()
