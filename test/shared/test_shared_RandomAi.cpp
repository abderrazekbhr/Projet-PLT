#include <boost/test/unit_test.hpp>
#include "engine.h"
#include "state.h"
#include "ai.h"

using namespace ai;
using namespace engine;
using namespace state;

BOOST_AUTO_TEST_SUITE(RandomAiTestSuite)

// Test case for RandomAi capturing a card
BOOST_AUTO_TEST_CASE(RandomAiCaptureCardTest)
{
    // Set up the game with 2 players, including 1 AI player.
    std::vector<std::string> playerNames = {"Player1", "RandomAI_1"};         // Names for the players
    SetUpGame *setUpGame = new SetUpGame(2, 11, playerNames, 'y', 1); // 2 players, max score 21, 1 AI

    Engine engine;                  // Create an engine to run the game
    engine.setActualCmd(setUpGame); // Set the game setup as the current command in the engine

    // Check if the game setup executed successfully. If not, fail the test.
    if (!setUpGame->execute(&engine))
    {
        BOOST_FAIL("Game setup failed.");
    }

    // Retrieve all players from the engine's state
    std::vector<Player *> players = engine.getState().getAllPlayers();

    // Attempt to cast the second player to a RandomAi object.
    RandomAi *randomAi = dynamic_cast<RandomAi *>(players[1]);
    if (!randomAi) // If cast fails, report the failure
    {
        BOOST_FAIL("Failed to cast Player to RandomAi.");
    }

    // Execute the RandomAI logic for the first time (AI makes its move).
    randomAi->run(&engine);

    // Add a card to the board and check the card holding logic for RandomAi
    GameBoard *board = engine.getState().getBoard();                  // Get the game board
    board->addCardToBoard(Card(NumberCard::deux, TypeCard::treffle)); // Add a card to the board
    Card card(NumberCard::deux, TypeCard::coeur);                     // Create a new card to be added to RandomAi's hand
    players[0]->addHoldCard(Card(NumberCard::un, TypeCard::coeur));   // Add a card to Player1's hand

    // Create a throw card action for Player1
    ThrowCard throwCard(0);
    engine.setActualCmd(&throwCard); // Set this throw action as the current command

    throwCard.execute(&engine); // Execute the throw card action

    // Add the created card to RandomAi's hand
    randomAi->addHoldedCard(card);

    // Check if RandomAi's hand now contains one card
    BOOST_CHECK_EQUAL(randomAi->getSizeHoldedCards(), 1);

    // Execute the RandomAI logic again (AI should make another move)
    randomAi->run(&engine);

    // Verify the state after RandomAI's execution
    BOOST_CHECK_EQUAL(randomAi->getHoldCard().size(), 0); // After running, RandomAi's hand should be empty
    BOOST_CHECK_EQUAL(board->getNumberCardBoard(), 1);    // The board should have 1 card after RandomAi's move

    // Add a new card to Player1's hand and RandomAi's hand for further testing
    players[0]->addHoldCard(Card(NumberCard::trois, TypeCard::coeur)); // Add card to Player1
    randomAi->addHoldCard(Card(NumberCard::valet, TypeCard::coeur));   // Add card to RandomAi

    // Create and execute a second throw action for Player1
    ThrowCard throwCard2(0);
    engine.setActualCmd(&throwCard2); // Set this throw action as the current command
    throwCard2.execute(&engine);      // Execute the throw action

    // RandomAi makes another move
    randomAi->run(&engine);

    // Check that RandomAi's hand is empty after the move
    BOOST_CHECK_EQUAL(randomAi->getSizeHoldedCards(), 0); // RandomAi's hand should be empty
    BOOST_CHECK_EQUAL(board->getNumberCardBoard(), 3);    // The board should have 3 cards after RandomAi's move
}

// End of test suite
BOOST_AUTO_TEST_SUITE_END()
