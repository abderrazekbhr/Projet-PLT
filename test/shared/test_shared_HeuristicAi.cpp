
#include <boost/test/unit_test.hpp>
#include "engine.h"
#include "state.h"
#include "ai.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace ai;
using namespace engine;
using namespace state;

BOOST_AUTO_TEST_CASE(test_heuristic_ai_full)
{
    // Set up the game with 2 players, including 1 AI player
    std::vector<std::string> playerNames = {"Player1", "Heuristic AI"};
    SetUpGame *setUpGame =new SetUpGame(2, 11, playerNames, 'y', 2); // 2 players, max score 11

    Engine engine;                  // Create an engine to run the game
    engine.setActualCmd(setUpGame); // Set the game setup as the current command in the engine

    // Check if the game setup executed successfully
    BOOST_CHECK_NO_THROW(engine.runCommand(&engine));

    // Retrieve all players from the engine's state
    auto &state = engine.getState();
    std::vector<Player *> players = state.getAllPlayers();
    BOOST_REQUIRE_EQUAL(players.size(), 2); // Ensure there are exactly 2 players

    // Get the AI player and board
    auto *heuristicAi = dynamic_cast<HeuristicAi *>(players[1]);
    BOOST_REQUIRE_MESSAGE(heuristicAi, "Failed to cast Player2 to HeuristicAi");
    auto *board = state.getBoard();
    BOOST_REQUIRE_MESSAGE(board, "Failed to retrieve the game board");

    // Set up cards for testing
    std::vector<Card> handPlayer = {
        Card(sept, pique),
        Card(trois, pique),
        Card(un, coeur)};

    std::vector<Card> handAi = {
        Card(sept, carreau),
        Card(roi, carreau),
        Card(un, treffle)};

    std::vector<Card> boardCards = {
        Card(trois, carreau),
        Card(quatre, carreau),
        Card(valet, pique)};

    // Add cards to the players and board
    for (int i = 0; i < 3; ++i)
    {
        players[0]->addHoldedCard(handPlayer[i]);
        heuristicAi->addHoldedCard(handAi[i]);
        board->addCardToBoard(boardCards[i]);
    }

    // Verify the cards were added correctly
    BOOST_CHECK_EQUAL(players[0]->getHoldCard().size(), 3);
    BOOST_CHECK_EQUAL(heuristicAi->getHoldCard().size(), 3);
    BOOST_CHECK_EQUAL(board->getCardBoard().size(), 3);

    // Test `checkPossibleChkoba`
    auto chkobaResult = heuristicAi->checkPossibleChkoba(handAi, boardCards);
    if (!chkobaResult["hand"].empty() && !chkobaResult["board"].empty())
    {
        BOOST_CHECK_EQUAL(chkobaResult["hand"].size(), 1); // Ensure only one card is played from hand
        BOOST_CHECK(!chkobaResult["board"].empty());       // Ensure cards on the board are involved
    }
    else
    {
        BOOST_CHECK(chkobaResult["hand"].empty() && chkobaResult["board"].empty());
    }

    // Test `checkPossible7Carreau`
    auto septCarreauResult = heuristicAi->checkPossible7Carreau(handAi, boardCards);
    if (!septCarreauResult["hand"].empty() && !septCarreauResult["board"].empty())
    {
        int handIndex = septCarreauResult["hand"][0];
        BOOST_CHECK_EQUAL(handAi[handIndex].getNumberCard(), 7); // Ensure the card is Sept
    }

    // Test `maximiseProfit`
    auto bestMove = heuristicAi->maximiseProfit(handAi, boardCards);
    if (!bestMove["hand"].empty() && !bestMove["board"].empty())
    {
        BOOST_CHECK(!bestMove["board"].empty());
        BOOST_CHECK(bestMove["hand"][0] < (int)handAi.size());
    }

    // Test `throwStrategy`
    int cardToThrow = heuristicAi->throwStrategy(handAi);
    BOOST_CHECK(cardToThrow >= 0 && cardToThrow < (int)handAi.size());

    // Test AI's `run` method
    BOOST_CHECK_NO_THROW(heuristicAi->run(&engine));

    // Test card collection logic
    heuristicAi->run(&engine);
    BOOST_CHECK_EQUAL(heuristicAi->getSizeCollectedCards(), 1);

    heuristicAi->run(&engine);
    BOOST_CHECK_EQUAL(heuristicAi->getSizeCollectedCards(), 1);

    // Optional: Test scoring logic if implemented
    // BOOST_CHECK_EQUAL(heuristicAi->getScore(), expectedScore);
}
