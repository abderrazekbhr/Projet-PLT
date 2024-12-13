#define BOOST_TEST_MODULE EngineTest
#include <boost/test/unit_test.hpp>
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
    BOOST_CHECK_EQUAL(currentState.turn, 0);

    // Incrémenter le tour
    currentState.incrementTurn();
    BOOST_CHECK_EQUAL(currentState.turn, 1);

    // Ajouter une validation supplémentaire pour s'assurer que les données de state sont cohérentes
    // Exemple : vérifier les joueurs, cartes ou autres composants liés à l'état
}

BOOST_AUTO_TEST_CASE(CommandManagementTest)
{
    // Test de la gestion des commandes
    engine::Engine engine;

    // Vérification initiale : la commande actuelle devrait être null
    BOOST_CHECK(engine.getCurrentCmd() == nullptr);

    // Création et affectation d'une commande ThrowCard
    engine::Command* throwCardCmd = new engine::ThrowCard(0); // Exemple d'index
    engine.setCurrentCmd(throwCardCmd);

    // Vérifier que la commande actuelle est bien throwCardCmd
    BOOST_CHECK(engine.getCurrentCmd() == throwCardCmd);

    // Exécution de la commande ThrowCard
    BOOST_CHECK_NO_THROW(engine.getCurrentCmd()->execute(&engine));

    // Création et affectation d'une commande CaptureCard
    std::vector<int> indicesBoard = {0}; // Exemple d'index pour les cartes du board
    engine::Command* captureCardCmd = new engine::CaptureCard(0, indicesBoard);
    engine.setCurrentCmd(captureCardCmd);

    // Vérifier que la commande actuelle est bien captureCardCmd
    BOOST_CHECK(engine.getCurrentCmd() == captureCardCmd);

    // Exécution de la commande CaptureCard
    BOOST_CHECK_NO_THROW(engine.getCurrentCmd()->execute(&engine));

    // Nettoyage (important pour éviter les fuites mémoire)
    engine.setCurrentCmd(nullptr);
    BOOST_CHECK(engine.getCurrentCmd() == nullptr);
}

 BOOST_AUTO_TEST_SUITE_END()
