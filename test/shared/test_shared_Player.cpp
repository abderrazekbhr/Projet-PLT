#define BOOST_TEST_MODULE Player
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "state.h"

using namespace state;

BOOST_AUTO_TEST_SUITE(Player_test)

// Test addToScore method
BOOST_AUTO_TEST_CASE(addToScoreTest)
{
    Player p1("BOB");
    p1.addToScore(10);
    BOOST_CHECK_EQUAL(p1.getScore(), 10);
}

// Test setName method
BOOST_AUTO_TEST_CASE(setNameTest)
{
    Player p1("BOB");
    p1.setName("TOM");
    BOOST_CHECK_EQUAL(p1.getName(), "TOM");
}

// Test addCollectedCard method
BOOST_AUTO_TEST_CASE(addCollectedCardTest)
{
    Player p1("BOB");
    NumberCard number = un;
    TypeCard types[] = {carreau, coeur, pique};

    for (int i = 0; i < 3; i++)
    {
        Card c1(number, types[i]);
        p1.addCollectedCard(c1);

        // Validate last card
        Card& lastCard = p1.getCollectCard()[i];
        BOOST_CHECK_EQUAL(lastCard.getNumberCard(), number);
        BOOST_CHECK_EQUAL(lastCard.getTypeCard(), types[i]);

        // Validate collection size
        int size = p1.getCollectCard().size();
        BOOST_CHECK_EQUAL(size, i + 1);
        BOOST_CHECK_EQUAL(p1.getSizeCollectedCards(), size);
    }
}

// Test addHoldCard method
BOOST_AUTO_TEST_CASE(addHoldCardTest)
{
    Player p1("BOB");
    NumberCard number = un;
    TypeCard types[] = {carreau, coeur, pique};

    for (int i = 0; i < 3; i++)
    {
        Card c1(number, types[i]);
        p1.addHoldCard(c1);

        // Validate last card
        Card& lastCard = p1.getHoldCard()[i];
        BOOST_CHECK_EQUAL(lastCard.getNumberCard(), number);
        BOOST_CHECK_EQUAL(lastCard.getTypeCard(), types[i]);

        // Validate hand size
        int size = p1.getHoldCard().size();
        BOOST_CHECK_EQUAL(size, i + 1);
        BOOST_CHECK_EQUAL(p1.getSizeHoldedCards(), size);
    }
}

// Test removeCardFromHand method
BOOST_AUTO_TEST_CASE(removeCardFromHandTest)
{
    Player p1("BOB");
    NumberCard number = un;
    TypeCard types[] = {carreau, coeur, pique};

    // Add cards to hand
    for (int i = 0; i < 3; i++)
    {
        Card c1(number, types[i]);
        p1.addHoldCard(c1);
    }

    // Remove a card
    Card c2(un, carreau);
    p1.removeCardFromHand(c2);

    // Validate hand size
    BOOST_CHECK_EQUAL(p1.getSizeHoldedCards(), 2);
}

// Test setPlayerStatus method
BOOST_AUTO_TEST_CASE(setPlayerStatusTest)
{
    Player p1("BOB");
    p1.setPlayerStatus(PLAYING);
    BOOST_CHECK_EQUAL(p1.getPlayerStatus(), PLAYING);
}

BOOST_AUTO_TEST_SUITE_END()
