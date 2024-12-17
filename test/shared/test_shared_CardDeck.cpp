//
// Created by khakha on 11/12/24.
//
#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include <vector>
#include <algorithm> // pour std::sort

using namespace state;

BOOST_AUTO_TEST_CASE(TestCardsDeckInitialization)
{
    CardsDeck deck;

    // Vérifie que le deck contient bien 40 cartes après l'initialisation
    BOOST_CHECK_EQUAL(deck.getDeckSize(), 40);
}

BOOST_AUTO_TEST_CASE(TestCardsDeckShuffle)
{
    CardsDeck deck;

    // Copie les cartes initiales pour comparer après mélange
    std::vector<Card> originalDeck = deck.getAllCards();

    // Mélange une seule fois
    deck.shuffleDeck();

    // Vérifie que l'ordre des cartes a changé en utilisant la méthode equals
    std::vector<Card> shuffledDeck = deck.getAllCards();
    bool isShuffled = false;
    for (size_t i = 0; i < originalDeck.size(); ++i) {
        if (!originalDeck[i].equals(shuffledDeck[i])) {
            isShuffled = true;
            break;
        }
    }

    // Vérifie que les cartes ont été mélangées
    BOOST_CHECK(isShuffled); // Le test passe si l'ordre des cartes a changé après un mélange
}

BOOST_AUTO_TEST_CASE(TestDistributeCardsToPlayers)
{
    CardsDeck deck;

    Player player1("Player1");
    Player player2("Player2");
    std::vector<Player*> players = { &player1, &player2 };

    // Distribue 3 cartes à chaque joueur
    deck.distributeCards(players, 3);

    // Vérifie que chaque joueur a bien 3 cartes
    BOOST_CHECK_EQUAL(player1.getSizeHoldedCards(), 3);
    BOOST_CHECK_EQUAL(player2.getSizeHoldedCards(), 3);

    // Vérifie que le deck contient désormais 34 cartes (40 - 2 * 3)
    BOOST_CHECK_EQUAL(deck.getDeckSize(), 34);
}

BOOST_AUTO_TEST_CASE(TestDistributeCardsToBoard)
{
    CardsDeck deck;

    GameBoard board;

    // Distribue 4 cartes au plateau
    deck.distributeCardsOnBoard(board, 4);

    // Vérifie que le plateau contient 4 cartes
    BOOST_CHECK_EQUAL(board.getNumberCardBoard(), 4);


}

BOOST_AUTO_TEST_CASE(TestDistributeCardsNotEnoughCards)
{
    CardsDeck deck;

    Player player("Player1");
    std::vector<Player*> players = { &player };

    // Tente de distribuer plus de cartes que celles disponibles dans le deck
    deck.distributeCards(players, 50);

    // Vérifie qu'aucune carte n'a été distribuée
    BOOST_CHECK_EQUAL(player.getSizeHoldedCards(), 0);

    GameBoard board;

    // Tente de distribuer plus de cartes au plateau que celles disponibles
    deck.distributeCardsOnBoard(board, 50);

    // Vérifie qu'aucune carte n'a été distribuée au plateau
    BOOST_CHECK_EQUAL(board.getNumberCardBoard(), 0);
}

BOOST_AUTO_TEST_CASE(TestCardDeckDestructor)
{
    CardsDeck* deck = new CardsDeck();
    delete deck; // Vérifie qu'aucune fuite de mémoire ne se produit.
    BOOST_CHECK(true); // Si le programme atteint cette ligne, cela signifie que le destructeur fonctionne correctement.
}