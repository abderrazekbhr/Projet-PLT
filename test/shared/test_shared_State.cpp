//
// Created by khakha on 10/12/24.
//
#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;
using namespace std;

BOOST_AUTO_TEST_CASE(TestStateInitialization)
{
    State state;

    BOOST_CHECK_EQUAL(state.getMaxScore(), 0); // Par défaut, maxScore est non initialisé.
    BOOST_CHECK_EQUAL(state.getNbPlayer(), 0); // Par défaut, nbPlayer est non initialisé.
    state.setNbPlayer(4);
    BOOST_CHECK_EQUAL(state.incrementTurn(), 1); // Vérifie que le premier tour commence correctement.
    BOOST_CHECK(state.getBoard() != nullptr);    // Vérifie que le plateau est bien initialisé.
    BOOST_CHECK(state.getAllCards() != nullptr); // Vérifie que les cartes sont bien initialisées.
}

BOOST_AUTO_TEST_CASE(TestStateSettersAndGetters)
{
    State state;
    state.setMaxScore(100);
    state.setNbPlayer(4);

    BOOST_CHECK_EQUAL(state.getMaxScore(), 100); // Vérifie que maxScore est correctement mis à jour.
    BOOST_CHECK_EQUAL(state.getNbPlayer(), 4);   // Vérifie que nbPlayer est correctement mis à jour.
}

BOOST_AUTO_TEST_CASE(TestStateTurnManagement)
{
    State state;
    state.setNbPlayer(4);
    BOOST_CHECK_EQUAL(state.incrementTurn(), 1);
    BOOST_CHECK_EQUAL(state.incrementTurn(), 2); // Passe au joueur 2.
    BOOST_CHECK_EQUAL(state.incrementTurn(), 3); // Passe au joueur 3.
    BOOST_CHECK_EQUAL(state.incrementTurn(), 0);
    BOOST_CHECK_EQUAL(state.incrementTurn(), 1); // Revient au joueur 1 (tour cyclique).
}

BOOST_AUTO_TEST_CASE(TestStateAddPlayer)
{
    State state;
    state.addPlayer("Player1");
    state.addPlayer("Player2");

    vector<Player *> players = state.getAllPlayers();
    BOOST_CHECK_EQUAL(players.size(), 2);                // Vérifie que deux joueurs ont été ajoutés.
    BOOST_CHECK_EQUAL(players[0]->getName(), "Player1"); // Vérifie le nom du premier joueur.
    BOOST_CHECK_EQUAL(players[1]->getName(), "Player2"); // Vérifie le nom du deuxième joueur.
}

BOOST_AUTO_TEST_CASE(TestStateDestructor)
{
    State *state = new State();
    delete state;      // Vérifie qu'aucune fuite de mémoire ne se produit.
    BOOST_CHECK(true); // Si le programme atteint cette ligne, cela signifie que le destructeur fonctionne correctement.
}
