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
    state.initCards();
    // Set up players and deck
    state.addPlayer("Player1");
    state.addPlayer("Player2");

    // Distribute all cards to players

    CardsDeck *deck = state.getAllCards();
    deck->distributeCards(state.getAllPlayers(), 3); // Example: give 3 cards to each player

    // Verify that the deck is empty after distribution
    BOOST_CHECK_EQUAL(deck->getDeckSize(), 34);

    // Distribute some cards to the board
    deck->distributeCardsOnBoard(*state.getBoard(), 3); // 3 cards on the board for the last round

    // Verify that there are cards on the board
    BOOST_CHECK_EQUAL(state.getBoard()->getNumberCardBoard(), 3);

    // Simulate the last player who captured a card
    state.setPlayerIndexForLastCapturedCard(0);

    // Remove all holded cards manually by overriding them (simulate an empty hand)
    for (auto *player : state.getAllPlayers())
    {
        while (!player->getHoldCard().empty())
        {
            player->getHoldCard().pop_back(); // Remove cards one by one
        }
        BOOST_CHECK(player->getHoldCard().empty()); // Ensure all players have no holded cards
    }

    // End the round
    EndRound endRound;

    // Execute the end of round
    bool result = endRound.execute(&engine);

    // Check if the round ended successfully
    BOOST_CHECK(result);

    // Verify that the player collected the cards from the board
    BOOST_CHECK_EQUAL(state.getAllPlayers()[0]->getSizeCollectedCards(), 3);

    // Verify that the board is empty after the round ends
    BOOST_CHECK_EQUAL(state.getBoard()->getNumberCardBoard(), 0);
}

BOOST_AUTO_TEST_CASE(test_end_round_players_have_holded_cards)
{
    Engine engine;
    state::State &state = engine.getState();

    // Add players
    state.addPlayer("Player1");
    state.addPlayer("Player2");

    // Give holded cards to players
    state.getAllPlayers()[0]->addHoldCard(state::Card(state::NumberCard::cinq, state::TypeCard::pique));
    state.getAllPlayers()[1]->addHoldCard(state::Card(state::NumberCard::valet, state::TypeCard::carreau));

    // Verify that players have holded cards
    BOOST_CHECK(!state.getAllPlayers()[0]->getHoldCard().empty());
    BOOST_CHECK(!state.getAllPlayers()[1]->getHoldCard().empty());

    // Simulate the last player who captured a card
    state.setPlayerIndexForLastCapturedCard(0);

    // Try to end the round
    EndRound endRound;
    bool result = endRound.execute(&engine);

    // The result should be false because players still have holded cards
    BOOST_CHECK(!result);
}

BOOST_AUTO_TEST_CASE(test_end_round_empty_board)
{
    Engine engine;
    state::State &state = engine.getState();

    // Add players
    state.addPlayer("Player1");
    state.addPlayer("Player2");
    CardsDeck *deck = state.getAllCards();

    // Empty the deck
    deck->distributeCards(state.getAllPlayers(), 20);

    // Ensure the board is empty
    BOOST_CHECK_EQUAL(state.getBoard()->getNumberCardBoard(), 0);

    // Remove all holded cards manually by overriding them (simulate an empty hand)
    for (auto *player : state.getAllPlayers())
    {
        while (!player->getHoldCard().empty())
        {
            player->getHoldCard().pop_back(); // Remove cards one by one
        }
        BOOST_CHECK(player->getHoldCard().empty()); // Ensure all players have no holded cards
    }

    // Set a valid player for the last capture
    state.setPlayerIndexForLastCapturedCard(0);

    // Try to end the round
    EndRound endRound;
    bool result = endRound.execute(&engine);

    // The result should be false because the board is empty
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
    deck->distributeCards(state.getAllPlayers(), 3);

    // Verify that the deck is empty after distribution
    BOOST_CHECK_EQUAL(deck->getDeckSize(), 34);

    // Distribute some cards to the board
    deck->distributeCardsOnBoard(*state.getBoard(), 3);

    // Verify that there are cards on the board
    BOOST_CHECK_EQUAL(state.getBoard()->getNumberCardBoard(), 3);

    // Simulate an invalid index for the last player who captured a card
    state.setPlayerIndexForLastCapturedCard(-1);

    // Remove all holded cards manually by overriding them (simulate an empty hand)
    for (auto *player : state.getAllPlayers())
    {
        while (!player->getHoldCard().empty())
        {
            player->getHoldCard().pop_back(); // Remove cards one by one
        }
        BOOST_CHECK(player->getHoldCard().empty());
    }

    // Try to end the round
    EndRound endRound;

    // Execute the end of round
    bool result = endRound.execute(&engine);

    // The result should be false due to invalid last capture index
    BOOST_CHECK(!result);
}

BOOST_AUTO_TEST_SUITE_END()
