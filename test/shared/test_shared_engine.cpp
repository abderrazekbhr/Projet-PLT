#include <boost/test/unit_test.hpp>
#include "engine.h"
#include <vector>

using namespace engine;


BOOST_AUTO_TEST_CASE(test_increment_turn)
{
    // Vérification de l'état initial du tour
    engine::Engine e = engine::Engine();
    state::State &state = e.getState();
    std::string n1 = "Player 1", n2 = "Player 2";
    state.addPlayer("Player 1");
    state.addPlayer("Player 2");
    state.setMaxScore(11);
    state.setNbPlayer(2);

    // Test pass to new player
    state::Player p = e.getActualPlayer();
    BOOST_CHECK_EQUAL(p.getName(), n1); 
    e.setNextPlayer();
    p = e.getActualPlayer();
    BOOST_CHECK_EQUAL(p.getName(), n2); 

    // Test command change set and get
    Command *command1 = new engine::RoundDistributeCards();
    e.setActualCmd(command1);
    Command *restGetCommand = e.getActualCommand();
    BOOST_CHECK_EQUAL(restGetCommand->getCMDTypeId(), DISTRIBUTE_CARD);
}
