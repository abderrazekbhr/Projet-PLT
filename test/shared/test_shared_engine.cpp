/*
    Engine ();
    ~Engine ();
    void init ();
    state::State& getState ();
    void setNextPlayer ();
    state::Player& getActualPlayer ();
*/
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "state.h"
#include "engine.h"
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;

BOOST_AUTO_TEST_SUITE(Engine_test)
BOOST_AUTO_TEST_CASE(all_test_engine){
    Engine * engine=new Engine();

}



