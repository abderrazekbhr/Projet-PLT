#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"

using namespace engine;
using namespace state;

BOOST_AUTO_TEST_SUITE(MyTestSuite)

BOOST_AUTO_TEST_CASE(test_count_score)
{
    // Create the engine and get the state (allocated on the stack)
    Engine engine;  // Allocated on the stack, no need for new here

    state::State& currentState = engine.getState();  // Retrieve the reference to the state

    // Add 3 players
    currentState.addPlayer("Player 1");
    currentState.addPlayer("Player 2");
    currentState.addPlayer("Player 3");

    // Create the cards
    Card card7Diamonds(NumberCard::sept, TypeCard::carreau);  // Seven of Diamonds
    Card card7Hearts(NumberCard::sept, TypeCard::coeur);      // Seven of Hearts
    Card card5Diamonds(NumberCard::cinq, TypeCard::carreau);  // Five of Diamonds
    Card card3Spades(NumberCard::trois, TypeCard::pique);     // Three of Spades
    Card card7Clubs(NumberCard::sept, TypeCard::treffle);     // Seven of Clubs
    Card card6Diamonds(NumberCard::six, TypeCard::carreau);   // Six of Diamonds

    // Distribute the cards
    Player* player1 = currentState.getAllPlayers()[0];
    Player* player2 = currentState.getAllPlayers()[1];
    Player* player3 = currentState.getAllPlayers()[2];

    // Player 1 has 3 cards (including "Seven of Diamonds")
    player1->addCollectedCard(card7Diamonds);
    player1->addCollectedCard(card5Diamonds);
    player1->addCollectedCard(card3Spades);

    // Player 2 has 2 cards (including "Seven of Hearts")
    player2->addCollectedCard(card7Hearts);
    player2->addCollectedCard(card5Diamonds);

    // Player 3 has 4 cards (including "Seven of Diamonds" and "Seven of Clubs")
    player3->addCollectedCard(card7Clubs);
    player3->addCollectedCard(card7Diamonds);
    player3->addCollectedCard(card6Diamonds);
    player3->addCollectedCard(card5Diamonds);

    // Create a CountScore object
    CountScore countScore;  // No need for new, allocated on the stack

    // Execute the CountScore::execute method
    countScore.execute(&engine);

    // Check the scores
    BOOST_CHECK_EQUAL(player1->getScore(), 1); // Player 1: +1 for "Seven of Diamonds" +1 for having the most cards (3 cards)
    BOOST_CHECK_EQUAL(player2->getScore(), 0); // Player 2: +1 for having "Seven of Hearts"
    BOOST_CHECK_EQUAL(player3->getScore(), 4); // Player 3: +1 for having the most cards (4 cards), +1 for having "Seven of Diamonds", +1 for having the most Sevens (2 Sevens), +1 for having the most Diamond cards (3 Diamond cards)

    BOOST_TEST_MESSAGE("Execute completed");

    // Cleanup is now automatically managed, no delete necessary
    BOOST_TEST_MESSAGE("Cleanup complete");
}

BOOST_AUTO_TEST_SUITE_END()
