#include <boost/test/unit_test.hpp>
#include <vector>
#include "../../src/shared/state.h"

using namespace ::state;
using namespace std;

BOOST_AUTO_TEST_CASE(TestGameBoard)
{
    // Test GameBoard Initialization
    GameBoard *gameBoard = new GameBoard();  // Dynamically create the GameBoard object
    BOOST_CHECK_EQUAL(gameBoard->getNumberCardBoard(), 0);  // Ensure the number of cards is 0 initially.

    // Test Adding a Card to the Board
    Card card1{NumberCard::un, TypeCard::treffle};  // Create a card with number "un" and type "treffle"
    gameBoard->addCardToBoard(card1);
    BOOST_CHECK_EQUAL(gameBoard->getNumberCardBoard(), 1);  // After adding the card, the number of cards should be 1.

    // Test Adding Another Card
    Card card2{NumberCard::deux, TypeCard::carreau};  // Create a card with number "deux" and type "carreau"
    gameBoard->addCardToBoard(card2);
    BOOST_CHECK_EQUAL(gameBoard->getNumberCardBoard(), 2);  // After adding another card, the number of cards should be 2.

    // Test Removing a Card from the Board
    gameBoard->removeCardBoard(card1);
    BOOST_CHECK_EQUAL(gameBoard->getNumberCardBoard(), 1);  // After removing card1, the number of cards should be 1.

    // Test Removing a Card That Does Not Exist
    gameBoard->removeCardBoard(card1);  // card1 has already been removed, so no change should occur
    BOOST_CHECK_EQUAL(gameBoard->getNumberCardBoard(), 1);  // The number of cards should remain 1.

    // Test Retrieving the Cards on the Board
    vector<Card> cards = gameBoard->getCardBoard();
    BOOST_CHECK_EQUAL(cards.size(), 1);  // Only card2 should remain on the board.
    BOOST_CHECK_EQUAL(cards[0].getNumberCard(), NumberCard::deux);  // card2's number should be "deux".
    BOOST_CHECK_EQUAL(cards[0].getTypeCard(), TypeCard::carreau);  // card2's type should be "carreau".

    // Delete the GameBoard object at the end of the test to free memory.
    delete gameBoard;  // Explicitly call the destructor to free the dynamically allocated memory.
}
