#include <boost/test/unit_test.hpp>
#include <vector>
#include "state/CardsDeck.h"
#include "state/State.h"

using namespace state;

BOOST_AUTO_TEST_SUITE(CardsDeckTests)

BOOST_AUTO_TEST_CASE(test_initial_deck_size) {
    // Création de l'objet State
    State currentState;

    // Obtenez le deck via getAllCards
    CardsDeck* deck = currentState.getAllCards();
    BOOST_REQUIRE(deck != nullptr); // Vérifie que le pointeur retourné n'est pas nul

    // Vérifie que le deck contient 40 cartes au départ
    BOOST_CHECK_EQUAL(deck->getAllCards().size(), 40);
}

BOOST_AUTO_TEST_CASE(test_shuffle_deck) {
    // Création de l'objet State
    State currentState;

    // Obtenez le deck via getAllCards
    CardsDeck* deck = currentState.getAllCards();
    BOOST_REQUIRE(deck != nullptr);

    // Mélange le deck et vérifie que le nombre de cartes reste inchangé
    deck->shuffleDeck();
    BOOST_CHECK_EQUAL(deck->getAllCards().size(), 40); // Vérifie que la taille reste à 40 après mélange
}

BOOST_AUTO_TEST_CASE(test_distribute_cards_to_players) {
    // Création de l'objet State
    State currentState;

    // Obtenez le deck via getAllCards
    CardsDeck* deck = currentState.getAllCards();
    BOOST_REQUIRE(deck != nullptr);

    // Simule la distribution de cartes aux joueurs
    std::vector<Player> players = {Player("Player1"), Player("Player2")};
    deck->distributeCards(players, 3);

    // Vérifie que chaque joueur a reçu 3 cartes
    for (auto& player : players) {
        BOOST_CHECK_EQUAL(player.getHoldCard().size(), 3);
    }

    // Vérifie que le deck a été réduit de 6 cartes (2 joueurs * 3 cartes chacun)
    BOOST_CHECK_EQUAL(deck->getAllCards().size(), 40 - 6);
}

BOOST_AUTO_TEST_CASE(test_distribute_cards_on_board) {
    // Création de l'objet State
    State currentState;

    // Obtenez le deck via getAllCards
    CardsDeck* deck = currentState.getAllCards();
    BOOST_REQUIRE(deck != nullptr);

    // Simule l'ajout de cartes sur le plateau de jeu
    GameBoard* board;
    deck->distributeCardsOnBoard(board, 5);

    // Vérifie que 5 cartes ont été placées sur le plateau
    BOOST_CHECK_EQUAL(board->getCardBoard().size(), 5);

    // Vérifie que le deck a encore été réduit de 5 cartes
    BOOST_CHECK_EQUAL(deck->getAllCards().size(), 40 - 6 - 5);
}

BOOST_AUTO_TEST_SUITE_END()
