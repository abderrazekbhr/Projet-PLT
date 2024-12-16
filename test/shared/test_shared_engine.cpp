#include <boost/test/unit_test.hpp>
#include "../../src/shared/engine.h"
#include <vector>

using namespace engine;

BOOST_AUTO_TEST_CASE(InitializationTest)
{
    // Test de l'initialisation de l'objet Engine
    engine::Engine engine;

    // Vérification de l'état initial de currentState
    state::State &currentState = engine.getState();
    currentState.setMaxScore(11);
    currentState.setNbPlayer(2);

    // Vérifier si les cartes et le plateau sont initialisés
    BOOST_CHECK_NO_THROW(currentState.initCards());
    BOOST_CHECK_NO_THROW(currentState.initBoard());

    // Vérifier que le plateau (board) contient des cartes
    BOOST_CHECK(engine.getState().getBoard()->getCardBoard().size() == 0); // Board initialisé, mais vide

    // Vérifier que le deck contient toutes les cartes
    BOOST_CHECK(engine.getState().getAllCards()->getDeckSize() > 0); // Deck doit contenir des cartes
}

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

    // Test pass to new palyer
    state::Player p = e.getActualPlayer();
    BOOST_CHECK_EQUAL(p.getName(), n1); // Le premier tour doit être 1
    e.setNextPlayer();
    p = e.getActualPlayer();
    BOOST_CHECK_EQUAL(p.getName(), n2); // Le tour doit revenir à 0 après avoir atteint 2

    // Test command change set and get
    Command *command1 = new engine::RoundDistributeCards();
    e.setActualCmd(command1);
    Command *restGetCommand = e.getActualCommand();
    BOOST_CHECK_EQUAL(restGetCommand->getCMDTypeId(), DISTRIBUTE_CARD);

}

