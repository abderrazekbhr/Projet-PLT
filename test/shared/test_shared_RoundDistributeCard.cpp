//
// Created by khakha on 15/12/24.
//
#include <boost/test/unit_test.hpp>
#include "engine.h"
#include "state.h"

BOOST_AUTO_TEST_CASE(TestRoundDistributeCards_Execute)
{
    // Crée une instance d'Engine et de RoundDistributeCards
    engine::Engine engine;
    engine::RoundDistributeCards roundDistribute;

    // Ajout de joueurs à l'état du jeu
    engine.getState().addPlayer("Player 1");
    engine.getState().addPlayer("Player 2");
    engine.getState().initCards();
    // Vérification de l'état initial
    BOOST_CHECK_EQUAL(engine.getState().getAllPlayers().size(), 2); // Vérifie qu'il y a bien 2 joueurs

    // Vérification que le deck existe et contient des cartes
    auto cardsDeck = engine.getState().getAllCards();
    BOOST_CHECK(cardsDeck);                            // Vérifie que le deck existe (non nul)
    size_t initialDeckSize = cardsDeck->getDeckSize(); // Stocke la taille initiale du deck
    BOOST_CHECK_GT(initialDeckSize, 0);                // Vérifie que le deck contient des cartes

    // Exécute la commande RoundDistributeCards
    BOOST_CHECK(roundDistribute.execute(&engine)); // Vérifie que l'exécution retourne true

    // Vérification de l'état après distribution
    auto playersAfter = engine.getState().getAllPlayers();
    BOOST_CHECK_EQUAL(playersAfter[0]->getSizeHoldedCards(), 3); // Le joueur 1 a 3 cartes
    BOOST_CHECK_EQUAL(playersAfter[1]->getSizeHoldedCards(), 3); // Le joueur 2 a 3 cartes

    // Vérifie que le deck a diminué de la bonne quantité (6 cartes retirées pour 2 joueurs)
    size_t cardsDistributed = 2 * 3; // 2 joueurs x 3 cartes
    BOOST_CHECK_EQUAL(cardsDeck->getDeckSize(), initialDeckSize - cardsDistributed);
}
