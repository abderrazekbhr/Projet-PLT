#define BOOST_TEST_MODULE EngineTest
#include <boost/test/included/unit_test.hpp>
#include "../../src/shared/engine.h"

using namespace engine; 
BOOST_AUTO_TEST_SUITE(EngineTestSuite)

BOOST_AUTO_TEST_CASE(InitializationTest)
{
    // Test de l'initialisation de l'objet Engine
    engine::Engine engine;

    // Vérification de l'état initial de currentState
    state::State& currentState = engine.getState();

    // Vérifier si les cartes et le plateau sont initialisés
    BOOST_CHECK_NO_THROW(currentState.initCards());
    BOOST_CHECK_NO_THROW(currentState.initBoard());

    // Initialiser les données
    engine.init();

    // Vérifier que le plateau (board) contient des cartes
    BOOST_CHECK(engine.getState().getBoard()->getCardBoard().size() == 0); // Board initialisé, mais vide

    // Vérifier que le deck contient toutes les cartes
    BOOST_CHECK(engine.getState().getAllCards()->getDeckSize() > 0); // Deck doit contenir des cartes
}

BOOST_AUTO_TEST_CASE(PlayerTurnTest)
{
    // Test de la gestion des joueurs et des tours
    engine::Engine engine;

    // Initialiser l'état et ajouter des joueurs
    state::State& currentState = engine.getState();
    currentState.addPlayer("Player 1");
    currentState.addPlayer("Player 2");

    // Vérifier que le joueur actuel est le premier
    BOOST_CHECK_EQUAL(engine.getActualPlayer().getName(), "Player 1");

    // Passer au joueur suivant
    engine.setNextPlayer();

    // Vérifier que le joueur actuel est maintenant le deuxième
    BOOST_CHECK_EQUAL(engine.getActualPlayer().getName(), "Player 2");
}

BOOST_AUTO_TEST_CASE(StateManagementTest)
{
    // Test pour s'assurer que currentState est bien manipulé
    engine::Engine engine;
    state::State& currentState = engine.getState();

    // Vérification de l'état initial
    BOOST_CHECK_EQUAL(currentState.getTurn(), 0);

    // Incrémenter le tour
    currentState.incrementTurn();
    BOOST_CHECK_EQUAL(currentState.getTurn(), 1);

    // Ajouter une validation supplémentaire pour s'assurer que les données de state sont cohérentes
    // Exemple : vérifier les joueurs, cartes ou autres composants liés à l'état
}

BOOST_AUTO_TEST_SUITE_END()
