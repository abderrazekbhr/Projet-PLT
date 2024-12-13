#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "state.h"
#include "engine.h"

using namespace state;
using namespace std;
BOOST_AUTO_TEST_SUITE(ThrowCard_test)

// test execute method
BOOST_AUTO_TEST_CASE(all_test)
{
    // Preparing new state
    engine::Engine *e = new engine::Engine();
    State s1 = e->getState();
    int nbPlayer = 2;
    int maxScore = 11;
    s1.setNbPlayer(nbPlayer);
    s1.setMaxScore(maxScore);
    s1.initBoard();
    s1.initCards();
    for (int i = 0; i < s1.getNbPlayer(); i++)
    {
        s1.addPlayer("User" + (i + 1));
    }

    GameBoard *board = s1.getBoard();
    int nbCardInBoardBefore = board->getNumberCardBoard();

    vector<Player *> players = s1.getAllPlayers();
    int size = 3;
    NumberCard numbersOfCards[] = {un, deux};
    TypeCard typesOfCards[] = {treffle, carreau};
    for (auto p : players)
    {
        for (int i = 0; i < size; i++)
        {
            Card *c = new Card(numbersOfCards[i], typesOfCards[i]);
            p->addHoldCard(*c);
        }
    }

    // Preparing Throw part
    int indexCard = 1;
    engine::ThrowCard *t = new engine::ThrowCard(indexCard);
    // Check CMDTypeId
    cout << "-----------------------" << t->getCMDTypeId() << "------------------------------" << endl;
    BOOST_CHECK_EQUAL(t->getCMDTypeId(), engine::THROW_CARD);

    // Check wrong logic
    // BOOST_CHECK_THROW(t->execute(e), std::out_of_range);
    // Check normale case when there is no exception
    t->indexCardHand = 0;
    bool result = t->execute(e);
    BOOST_CHECK(result == true);
    int nbCardInBoardAfter = board->getNumberCardBoard();
    BOOST_CHECK(nbCardInBoardAfter == (nbCardInBoardBefore + 1));
}
BOOST_AUTO_TEST_SUITE_END()
