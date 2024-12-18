//
// Created by khakha on 11/12/24.
//

#include <boost/test/unit_test.hpp>
#include "engine.h"
#include "state.h"

BOOST_AUTO_TEST_CASE(TestRoundInitDistributeCards_Execute_Y)
{
    // Crée une instance d'Engine
    engine::Engine engine;

    // Polymorphisme : Utilise un pointeur vers la classe de base Command
    engine::Command* roundInit = new engine::RoundInitDistributeCards('Y'); // Réponse 'Y'

    // Ajout de joueurs à l'état du jeu
    engine.getState().addPlayer("Player 1");
    engine.getState().addPlayer("Player 2");

    // Vérification de l'état initial
    BOOST_CHECK_EQUAL(engine.getState().getAllPlayers().size(), 2); // Vérifie qu'il y a bien 2 joueurs

    // Vérifie que le deck existe et contient des cartes
    BOOST_CHECK_NE(engine.getState().getAllCards(), nullptr);  // Vérifie que le deck existe
    BOOST_CHECK_GT(engine.getState().getAllCards()->getDeckSize(), 0); // Vérifie que le deck contient des cartes

    // Exécute la commande via le pointeur polymorphique
    BOOST_CHECK(roundInit->execute(&engine)); // Vérifie que l'exécution réussit

    // Vérification de l'état après distribution
    auto playersAfter = engine.getState().getAllPlayers();
    BOOST_CHECK_EQUAL(playersAfter[0]->getSizeHoldedCards(), 3); // Le joueur 1 a 3 cartes
    BOOST_CHECK_EQUAL(playersAfter[1]->getSizeHoldedCards(), 3); // Le joueur 2 a 3 cartes
    BOOST_CHECK_EQUAL(engine.getState().getBoard()->getNumberCardBoard(), 4); // 4 cartes sur le plateau

    // Libère la mémoire
    //delete roundInit;
}

BOOST_AUTO_TEST_CASE(TestRoundInitDistributeCards_Execute_N)
{
    // Crée une instance d'Engine
    engine::Engine engine;

    // Polymorphisme : Utilise un pointeur vers la classe de base Command
    engine::Command* roundInit = new engine::RoundInitDistributeCards('N'); // Réponse 'N'

    // Ajout de joueurs à l'état du jeu
    engine.getState().addPlayer("Player 1");
    engine.getState().addPlayer("Player 2");

    // Vérification de l'état initial
    BOOST_CHECK_EQUAL(engine.getState().getAllPlayers().size(), 2); // Vérifie qu'il y a bien 2 joueurs

    // Vérifie que le deck existe et contient des cartes
    BOOST_CHECK_NE(engine.getState().getAllCards(), nullptr);  // Vérifie que le deck existe
    BOOST_CHECK_GT(engine.getState().getAllCards()->getDeckSize(), 0); // Vérifie que le deck contient des cartes

    // Exécute la commande via le pointeur polymorphique
    BOOST_CHECK(roundInit->execute(&engine)); // Vérifie que l'exécution réussit

    // Vérification de l'état après distribution
    auto playersAfter = engine.getState().getAllPlayers();
    BOOST_CHECK_EQUAL(playersAfter[0]->getSizeHoldedCards(), 3); // Le joueur 1 a 3 cartes
    BOOST_CHECK_EQUAL(playersAfter[1]->getSizeHoldedCards(), 3); // Le joueur 2 a 3 cartes
    BOOST_CHECK_EQUAL(engine.getState().getBoard()->getNumberCardBoard(), 4); // 4 cartes sur le plateau

    // Libère la mémoire
    //delete roundInit;
}
