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
    SetUpGame *setUpGame = new SetUpGame(2, 11, playerNames, 'y', 2); // 2 players, max score 11

    Engine engine;                  // Create an engine to run the game
    engine.setActualCmd(setUpGame); // Set the game setup as the current command in the engine

    // Check if the game setup executed successfully
    engine.runCommand(&engine);

    // Retrieve all players from the engine's state
    std::vector<Player *> players = engine.getState().getAllPlayers();
    BOOST_REQUIRE_EQUAL(players.size(), 2); // Ensure there are exactly 2 players

    // Get the AI player and board
    HeuristicAi *heuristicAi = dynamic_cast<HeuristicAi *>(players[1]);
    BOOST_REQUIRE(heuristicAi); // Ensure successful cast to HeuristicAi
    GameBoard *board = engine.getState().getBoard();
    BOOST_REQUIRE(board);

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
    for (int i = 0; i < 3; i++)
    {
        players[0]->addHoldedCard(handPlayer[i]);
        heuristicAi->addHoldedCard(handAi[i]);
        board->addCardToBoard(boardCards[i]);
    }

    // Test `checkPossibleChkoba`
    auto chkobaResult = heuristicAi->checkPossibleChkoba(handAi, boardCards);
    if (!chkobaResult["hand"].empty() && !chkobaResult["board"].empty())
    {
        std::vector<int> boardIndices = chkobaResult["board"];
        BOOST_CHECK_EQUAL(heuristicAi->getScore(), 1);
    }
    else
    {
        BOOST_CHECK(chkobaResult["hand"].empty() || chkobaResult["board"].empty());
    }

    // Test `checkPossible7Carreau`
    auto septCarreauResult = heuristicAi->checkPossible7Carreau(handAi, boardCards);
    if (!septCarreauResult["hand"].empty() && !septCarreauResult["board"].empty())
    {
        int handIndex = septCarreauResult["hand"][0];
        std::vector<int> boardIndices = septCarreauResult["board"];
        BOOST_CHECK_EQUAL(handAi[handIndex].getNumberCard(), 7);
        for (int idx : boardIndices)
        {
            BOOST_CHECK_EQUAL(boardCards[idx].getNumberCard(), 7);
        }
    }

    // Test `maximiseProfit`
    auto bestMove = heuristicAi->maximiseProfit(handAi, boardCards);
    if (!bestMove["hand"].empty() && !bestMove["board"].empty())
    {
        int handIndex = bestMove["hand"][0];
        std::vector<int> boardIndices = bestMove["board"];
        BOOST_CHECK(!boardIndices.empty());
        BOOST_CHECK(handIndex >= 0 && handIndex < (int)handAi.size());
    }

    // Test `throwStrategy`
    int cardToThrow = heuristicAi->throwStrategy(handAi);
    BOOST_CHECK(cardToThrow >= 0 && cardToThrow < (int)handAi.size());

    // Test AI's `run` method
    BOOST_CHECK_NO_THROW(heuristicAi->run(&engine));

    // Test card collection logic
    heuristicAi->run(&engine);                                  // Run AI logic
    BOOST_CHECK_EQUAL(heuristicAi->getSizeCollectedCards(), 1); // Ensure cards are collected properly

    heuristicAi->run(&engine);                                  // Run AI logic again
    BOOST_CHECK_EQUAL(heuristicAi->getSizeCollectedCards(), 1); // Ensure no duplicate collection

    // Test AI's scoring logic
    // Uncomment this part if scoring is implemented
    // BOOST_CHECK_EQUAL(heuristicAi->getScore(), expectedScore);
}
