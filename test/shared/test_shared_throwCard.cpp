#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "state.h"
#include "engine.h"

using namespace state;
using namespace std;

BOOST_AUTO_TEST_SUITE(ThrowCard_test)

// Test the execute method of ThrowCard
BOOST_AUTO_TEST_CASE(all_test)
{
    // Create and initialize engine
    engine::Engine e = engine::Engine();

    // Get the game state and configure it
    State &s1 = e.getState(); // Use reference to avoid copying
    int nbPlayer = 2;
    int maxScore = 11;
    s1.setNbPlayer(nbPlayer);
    s1.setMaxScore(maxScore);
    s1.initBoard();
    s1.initCards();

    // Add players
    s1.turn = 0;
    for (int i = 0; i < s1.getNbPlayer(); i++)
    {
        s1.addPlayer("User" + to_string(i + 1)); // Corrected string concatenation
    }

    // Get the game board and initial card count
    GameBoard *board = s1.getBoard();
    BOOST_REQUIRE(board != nullptr); // Ensure board is properly initialized
    int nbCardInBoardBefore = board->getNumberCardBoard();

    // Add cards to players
    vector<Player *> players = s1.getAllPlayers();
    int size = 2; // Match size to the number of cards in `numbersOfCards` and `typesOfCards`
    NumberCard numbersOfCards[] = {un, deux};
    TypeCard typesOfCards[] = {treffle, carreau};
    for (auto p : players)
    {
        for (int i = 0; i < size; i++)
        {
            Card c = Card(numbersOfCards[i], typesOfCards[i]);
            p->addHoldCard(c);
        }
    }

    // Prepare ThrowCard command
    int indexCard = 0;
    engine::ThrowCard *t = new engine::ThrowCard(indexCard);

    // Check CMDTypeId
    BOOST_CHECK_EQUAL(t->getCMDTypeId(), engine::THROW_CARD);

    // Test invalid case: index out of bounds
    t->indexCardHand = 5; // Invalid index
    BOOST_CHECK_EQUAL(t->execute(&e), false);

    // Test valid case: index in bounds
    t->indexCardHand = 0; // Valid index
    bool result = t->execute(&e);
    BOOST_CHECK_EQUAL(result, true);

    // Validate board state
    int nbCardInBoardAfter = board->getNumberCardBoard();
    BOOST_CHECK_EQUAL(nbCardInBoardAfter, nbCardInBoardBefore + 1);
}

BOOST_AUTO_TEST_SUITE_END()
