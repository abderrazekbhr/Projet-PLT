#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "state.h"
#include <iostream>
using namespace std;
using namespace state;

BOOST_AUTO_TEST_SUITE(Player_test)

BOOST_AUTO_TEST_CASE(all_tests_Player)
{
    // Test Constructor
    Player *p1 = new Player("BOB");
    BOOST_CHECK_EQUAL(p1->getName(), "BOB");

    // Test addToScore method
    p1->addToScore(10);
    BOOST_CHECK_EQUAL(p1->getScore(), 10);

    // Test setName method
    p1->setName("TOM");
    BOOST_CHECK_EQUAL(p1->getName(), "TOM");

    // Correctly initialize enums
    NumberCard number = un;                     // First card number
    TypeCard types[] = {carreau, coeur, pique}; // Card types

    for (int i = 0; i < 3; i++)
    {
        Card *c1 = new Card(number, types[i]); // Create card with number and type
        p1->addCollectedCard(*c1);             // Add card to collected cards

        // Check if the last card in collected cards matches
        Card lastCard = p1->getCollectCard()[i];
        bool isEquals = lastCard.getNumberCard() == number && lastCard.getTypeCard() == types[i];

        // Correct assertions
        BOOST_CHECK(isEquals);

        // Check size of collected cards
        int size = p1->getCollectCard().size();
        BOOST_CHECK_EQUAL(size, i + 1);
        BOOST_CHECK_EQUAL(p1->getSizeCollectedCards(), size);
    }

    // test add to hold card
    for (int i = 0; i < 3; i++)
    {
        Card *c1 = new Card(number, types[i]); // Create card with number and type
        p1->addHoldCard(*c1);                  // Add card to collected cards

        // Check if the last card in collected cards matches
        Card lastCard = p1->getHoldCard()[i];
        bool isEquals = lastCard.getNumberCard() == number && lastCard.getTypeCard() == types[i];

        // Correct assertions
        BOOST_CHECK(isEquals);

        // Check size of collected cards
        int size = p1->getHoldCard().size();
        BOOST_CHECK_EQUAL(size, i + 1);
        BOOST_CHECK_EQUAL(p1->getSizeHoldedCards(), size);
    }

    // Test removeCardFromHand method
    // Remove a card
    Card c2(un, carreau);
    p1->removeCardFromHand(c2);

    // Validate hand size
    BOOST_CHECK_EQUAL(p1->getSizeHoldedCards(), 2);

    // Test setPlayerStatus method
    p1->setPlayerStatus(PLAYING);
    BOOST_CHECK_EQUAL(p1->getPlayerStatus(), PLAYING);

    delete p1;
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
