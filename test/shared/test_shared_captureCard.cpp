#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "state.h"
#include "engine.h"

using namespace state;
using namespace std;

BOOST_AUTO_TEST_SUITE(CaptureCard_test)

// Test the execute method of CaptureCard
BOOST_AUTO_TEST_CASE(all_test)
{
    // Create and initialize engine
    engine::Engine e;

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
        s1.addPlayer("User" + to_string(i + 1));
    }

    // Get the game board and initial card count
    GameBoard *board = s1.getBoard();
    BOOST_REQUIRE(board != nullptr);

    // Add cards to players
    vector<Player *> players = s1.getAllPlayers();
    NumberCard numbersOfCards[] = {sept, deux};
    TypeCard typesOfCards[] = {treffle, carreau};
    for (auto p : players)
    {
        for (int i = 0; i < 2; i++)
        {
            Card c(numbersOfCards[i], typesOfCards[i]);
            p->addHoldCard(c);
        }
    }

    // Add cards to the board
    board->addCardToBoard(Card(trois, pique));
    board->addCardToBoard(Card(quatre, pique));

    int nbCardInBoardBefore = board->getNumberCardBoard();

    // Prepare CaptureCard command
    engine::CaptureCard capt(1, {0, 1});

    // Check CMDTypeId
    BOOST_CHECK_EQUAL(capt.getCMDTypeId(), engine::CAPTURE_CARD);

    // Test invalid case: incorrect sum (if a validation for sum exists in game rules)
    BOOST_CHECK_EQUAL(capt.execute(&e), false);

    // Test invalid case: index out of bounds from card hand
    capt.indexCardHand = 5; // Invalid index
    BOOST_CHECK_EQUAL(capt.execute(&e), false);

    for (auto c : board->getCardBoard())
    {
        cout << "Card on board: " << c.getNumberCard() << " " << c.getTypeCard() << endl;
    }
    // Test invalid case: index out of bounds from card board
    capt.indexCardHand = 0;         // Valid index
    capt.indexsCardsBoard = {0, 5}; // Invalid board index
    BOOST_CHECK_EQUAL(capt.execute(&e), false);
    for (auto c : board->getCardBoard())
    {
        cout << "Card on board: " << c.getNumberCard() << " " << c.getTypeCard() << endl;
    }
    // Test valid capture card with correct index and correct board index
    capt.indexCardHand = 0;
    capt.indexsCardsBoard = {0, 1};
    BOOST_CHECK_EQUAL(capt.execute(&e), true);

    // Validate board state
    int nbCardInBoardAfter = board->getNumberCardBoard();
    BOOST_CHECK_EQUAL(nbCardInBoardAfter, nbCardInBoardBefore - 2); // Two cards were captured

    // Validate player state
    BOOST_CHECK_EQUAL(players[0]->getSizeHoldedCards(), 1);    // One card left in hand
    BOOST_CHECK_EQUAL(players[0]->getSizeCollectedCards(), 3); // Includes 1 hand card + 2 board cards

    // Validate player score
    BOOST_CHECK_EQUAL(players[0]->getScore(), 1); // Score increment due to chkoba
}

BOOST_AUTO_TEST_SUITE_END();
