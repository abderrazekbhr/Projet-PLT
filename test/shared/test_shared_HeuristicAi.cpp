
#include <boost/test/unit_test.hpp>
#include "engine.h"
#include "state.h"
#include "ai.h"

using namespace ai;
using namespace engine;
using namespace state;

BOOST_AUTO_TEST_SUITE(HeuristicAiTestSuite)

// Test case for HeuristicAi capturing a card
BOOST_AUTO_TEST_CASE(HeuristicAiCaptureCardTest)
{
    // Set up the game with 2 players, including 1 AI player.
    std::vector<std::string> playerNames = {"Player1", "Heuristic AI"}; // Names for the players
    SetUpGame *setUpGame = new SetUpGame(2, 4, playerNames, 'y', 2); // 2 players, max score 21, 1 AI

    Engine engine;                  // Create an engine to run the game
    engine.setActualCmd(setUpGame); // Set the game setup as the current command in the engine

    // Check if the game setup executed successfully. If not, fail the test.
    BOOST_REQUIRE(setUpGame->execute(&engine));

    // Retrieve all players from the engine's state
    std::vector<Player *> players = engine.getState().getAllPlayers();

    // Ensure the second player is of type HeuristicAi
    auto *heuristicAi = dynamic_cast<HeuristicAi *>(players[1]);
    if (!heuristicAi) // If cast fails, report the failure
    {
        BOOST_FAIL("Failed to cast Player to heuristicAI.");
    }
    // Setup the game state: Add cards to players and board
    GameBoard *board = engine.getState().getBoard(); // Get the game board
    players[0]->addHoldCard(Card(NumberCard::un, TypeCard::coeur));   // Add card to Player1's hand
    heuristicAi->addHoldedCard(Card(NumberCard::trois, TypeCard::pique)); // Add card to HeuristicAi's hand
    board->addCardToBoard(Card(NumberCard::trois, TypeCard::carreau)); // Add card to the board

    // Verify the cards were added correctly
    BOOST_CHECK_EQUAL(players[0]->getHoldCard().size(), 1); // Player1 should have 1 card
    BOOST_CHECK_EQUAL(heuristicAi->getHoldCard().size(), 1); // Heuristic AI should have 1 card
    BOOST_CHECK_EQUAL(board->getNumberCardBoard(), 1); // The board should have 1 card

    // Test if Heuristic AI can capture a card (simulate the AI move)
    heuristicAi->run(&engine);  // Execute the AI logic
    heuristicAi->run(&engine);  // Execute the AI logic

    // Check that the AI collected a card after the move
    BOOST_CHECK_EQUAL(heuristicAi->getSizeCollectedCards(), 2); // The AI should have collected 1 card
    BOOST_CHECK_EQUAL(board->getNumberCardBoard(), 1); // The board should be empty after the capture

    // Add more cards and make a second move for the AI
    players[0]->addHoldCard(Card(NumberCard::sept, TypeCard::coeur));   // Add card to Player1's hand
    heuristicAi->addHoldedCard(Card(NumberCard::quatre, TypeCard::coeur)); // Add card to HeuristicAi's hand
    board->addCardToBoard(Card(NumberCard::trois, TypeCard::pique)); // Add card to the board
    board->addCardToBoard(Card(NumberCard::un, TypeCard::pique)); // Add card to the board

    // Simulate the AI move again
    heuristicAi->run(&engine);
    heuristicAi->run(&engine);

    // Check if the AI performed another move and collected cards
    BOOST_CHECK_EQUAL(heuristicAi->getSizeCollectedCards(), 5); // The AI should have collected 2 cards
    BOOST_CHECK_EQUAL(board->getNumberCardBoard(), 2); // The board should be empty after the second capture

    // Final check to verify that the state is correct
    BOOST_CHECK_EQUAL(heuristicAi->getHoldCard().size(), 0); // Heuristic AI should have 1 card left after making moves
    BOOST_CHECK_EQUAL(players[0]->getHoldCard().size(), 0);  // Player1 should have 1 card left
    players[0]->addHoldCard(Card(NumberCard::sept, TypeCard::coeur));   // Add card to Player1's hand
    heuristicAi->addHoldedCard(Card(NumberCard::un, TypeCard::coeur)); // Add card to HeuristicAi's hand
    heuristicAi->run(&engine);
    heuristicAi->run(&engine);
    BOOST_CHECK_EQUAL(heuristicAi->getSizeCollectedCards(), 7); // The AI should have collected 2 cards
    BOOST_CHECK_EQUAL(board->getNumberCardBoard(), 0); // The board should be empty after the second capture
    heuristicAi->addHoldedCard(Card(NumberCard::un, TypeCard::coeur)); // Add card to HeuristicAi's hand
    heuristicAi->addHoldedCard(Card(NumberCard::sept, TypeCard::carreau)); // Add card to HeuristicAi's hand
    players[0]->addHoldCard(Card(NumberCard::deux, TypeCard::coeur));   // Add card to Player1's hand

    board->addCardToBoard(Card(NumberCard::sept, TypeCard::treffle)); // Add card to the board
    board->addCardToBoard(Card(NumberCard::sept, TypeCard::coeur)); // Add card to the board
    board->addCardToBoard(Card(NumberCard::un, TypeCard::carreau)); // Add card to the board
    heuristicAi->run(&engine);
    heuristicAi->run(&engine);
    BOOST_CHECK_EQUAL(heuristicAi->getSizeCollectedCards(), 9); // The AI should have collected 2 cards

}

BOOST_AUTO_TEST_SUITE_END()
