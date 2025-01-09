#include <boost/test/unit_test.hpp>
#include "engine/EndRound.h"
#include "engine/Engine.h"
#include "state/State.h"
#include "state/CardsDeck.h"
#include "state/Player.h"
#include "state/GameBoard.h"

using namespace state;
using namespace engine;

BOOST_AUTO_TEST_SUITE(EndRoundTests)

BOOST_AUTO_TEST_CASE(test_end_round_successful)
{
    Engine engine;
    state::State &state = engine.getState();

    // Set up players and deck
    state.addPlayer("Player1");
    state.addPlayer("Player2");

    // Distribute all cards to players
    CardsDeck *deck = state.getAllCards();

    // Distribute all cards, ensuring the deck is empty afterward
    deck->distributeCards(state.getAllPlayers(), 3); // Example: give 3 cards to each player

    // Verify that the deck is empty after distribution
    BOOST_CHECK_EQUAL(deck->getDeckSize(), 34);

    // Distribute some cards to the board (since it's the last round, assume this step is required)
    deck->distributeCardsOnBoard(*state.getBoard(), 3); // 3 cards on the board for the last round

    // Verify that there are cards on the board
    BOOST_CHECK_EQUAL(state.getBoard()->getNumberCardBoard(), 3);
    BOOST_CHECK_EQUAL(deck->getDeckSize(), 31);
    deck->distributeCards(state.getAllPlayers(), 3);
    deck->distributeCards(state.getAllPlayers(), 3);
    deck->distributeCards(state.getAllPlayers(), 3);
    deck->distributeCards(state.getAllPlayers(), 3);
    deck->distributeCardsOnBoard(*state.getBoard(), 7);
    BOOST_CHECK_EQUAL(deck->getDeckSize(), 0);

    // Simulate the last player who captured a card
    state.setPlayerIndexForLastCapturedCard(0);

    // End the round
    EndRound endRound;

    // Execute the end of round
    bool result = endRound.execute(&engine);

    // Check if the round ended successfully
    BOOST_CHECK(result);

    // Verify that the player collected the cards from the board
    BOOST_CHECK_EQUAL(state.getAllPlayers()[0]->getSizeCollectedCards(), 10);

    // Verify that the board is empty after the round ends
    BOOST_CHECK_EQUAL(state.getBoard()->getNumberCardBoard(), 0);

    // Verify the deck size remains 0 (no change as no cards are added back to the deck)
    BOOST_CHECK_EQUAL(deck->getDeckSize(), 0);
}


BOOST_AUTO_TEST_CASE(test_end_round_deck_not_empty)
{
    Engine engine;
    state::State &state = engine.getState();

    // Ajouter des joueurs
    state.addPlayer("Player1");
    state.addPlayer("Player2");

    // Vérifier que le deck contient encore des cartes
    BOOST_CHECK_GT(state.getAllCards()->getDeckSize(), 0);

    // Essayer de terminer la manche
    EndRound endRound;
    bool result = endRound.execute(&engine);

    // Le résultat doit être false
    BOOST_CHECK(!result);
}
BOOST_AUTO_TEST_CASE(test_end_round_empty_board)
{
    Engine engine;
    state::State &state = engine.getState();

    // Ajouter des joueurs
    state.addPlayer("Player1");
    state.addPlayer("Player2");
    CardsDeck *deck = state.getAllCards();

    // Vider le deck
    deck->distributeCards(state.getAllPlayers(), 20); // Example: give 3 cards to each player

    // Assurer que le plateau est vide
    BOOST_CHECK_EQUAL(state.getBoard()->getNumberCardBoard(), 0);

    // Définir un joueur valide pour la dernière capture
    state.setPlayerIndexForLastCapturedCard(0);

    // Essayer de terminer la manche
    EndRound endRound;
    bool result = endRound.execute(&engine);

    // Le résultat doit être false
    BOOST_CHECK(!result);
}

BOOST_AUTO_TEST_CASE(test_end_round_invalid_last_capture_index)
{
    Engine engine;
    state::State &state = engine.getState();

    // Set up players and deck
    state.addPlayer("Player1");
    state.addPlayer("Player2");

    // Distribute all cards to players
    CardsDeck *deck = state.getAllCards();

    // Distribute all cards, ensuring the deck is empty afterward
    deck->distributeCards(state.getAllPlayers(), 3); // Example: give 3 cards to each player

    // Verify that the deck is empty after distribution
    BOOST_CHECK_EQUAL(deck->getDeckSize(), 34);

    // Distribute some cards to the board (since it's the last round, assume this step is required)
    deck->distributeCardsOnBoard(*state.getBoard(), 3); // 3 cards on the board for the last round

    // Verify that there are cards on the board
    BOOST_CHECK_EQUAL(state.getBoard()->getNumberCardBoard(), 3);
    BOOST_CHECK_EQUAL(deck->getDeckSize(), 31);
    deck->distributeCards(state.getAllPlayers(), 3);
    deck->distributeCards(state.getAllPlayers(), 3);
    deck->distributeCards(state.getAllPlayers(), 3);
    deck->distributeCards(state.getAllPlayers(), 3);
    deck->distributeCardsOnBoard(*state.getBoard(), 7);
    BOOST_CHECK_EQUAL(deck->getDeckSize(), 0);

    // Simulate the last player who captured a card
    state.setPlayerIndexForLastCapturedCard(-1);

    // End the round
    EndRound endRound;

    // Execute the end of round
    bool result = endRound.execute(&engine);

    // Check if the round ended successfully
    BOOST_CHECK(!result);

    // Verify that the player collected the cards from the board
    BOOST_CHECK_EQUAL(state.getAllPlayers()[0]->getSizeCollectedCards(), 0);

    // Verify that the board is empty after the round ends
    BOOST_CHECK_EQUAL(state.getBoard()->getNumberCardBoard(), 10);

    // Verify the deck size remains 0 (no change as no cards are added back to the deck)
    BOOST_CHECK_EQUAL(deck->getDeckSize(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
