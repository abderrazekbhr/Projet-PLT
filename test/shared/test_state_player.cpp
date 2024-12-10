// Player (std::string name);
//     std::vector<Card> getHoldCard ();
//     void addHoldCard (Card card);
//     PlayerStatus getPlayerStatus ();
//     void setPlayerStatus (PlayerStatus newStatus);
//     Card selectCardFromHand (int cardIndex);
//     void addHoldedCard (Card card);
//     void removeCardFromHand (Card card);
//     ~Player ();

#define BOOST_TEST_MODULE Player
#include <boost/test/included/unit_test.hpp>
#include "state.h"
#include <iostream>

using namespace state;
Player *p1 = new Player("BOB");

BOOST_AUTO_TEST_SUITE(Player_test);

// test addToScore method
BOOST_AUTO_TEST_CASE(addToScoreTest)
{
    p1->addToScore(10);
    BOOST_CHECK(p1->getScore() == 10);
}

// test setName method
BOOST_AUTO_TEST_CASE(setNameTest)
{
    p1->setName("TOM");
    BOOST_CHECK_EQUAL(p1->getName(), "TOM");
}

// test addCollectedCard method
BOOST_AUTO_TEST_CASE(addCollectedCardTest)
{
    // create multiple cards and add them to the player's collected cards
    NumberCard number = un;
    TypeCard types[] = {carreau, coeur, pique};
    for (int i = 0; i < 3; i++)
    {
        Card *c1 = new Card(number, types[i]);
        p1->addCollectedCard(*c1);
        Card lastCard = p1->getCollectCard()[i];
        int size = p1->getCollectCard().size();
        bool isEquals = lastCard.getNumberCard() == number && lastCard.getTypeCard() == types[i];
        BOOST_CHECK_EQUAL(size, i + 1);
        BOOST_CHECK(isEquals);
    }
}

BOOST_AUTO_TEST_SUITE_END()
