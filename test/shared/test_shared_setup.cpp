#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <vector>

#include "../../src/shared/engine.h"
#include "../../src/shared/state.h"
using namespace engine;
using namespace state;

BOOST_AUTO_TEST_SUITE(SetUpGameTests)

// Test with valid configuration (correct number of players and score)
BOOST_AUTO_TEST_CASE(test_execute_valid) {
    std::vector<std::string> players = {"Alice", "Bob"};
    SetUpGame setup(2, 11, players);

    Engine engine;

    // Test if the execute method works via polymorphism using Command*
    Command* command = &setup;  // Base class pointer
    BOOST_CHECK(command->execute(&engine));  // Polymorphic call to execute
}

// Test with an invalid configuration (incorrect number of players)
BOOST_AUTO_TEST_CASE(test_execute_invalid_number_of_players) {
    std::vector<std::string> players = {"Alice", "Bob", "Charlie"};
    SetUpGame setup(3, 11, players);

    Engine engine;

    // Test if an exception is thrown when the number of players is incorrect
    Command* command = &setup;
    BOOST_CHECK_THROW(command->execute(&engine), std::invalid_argument);
}

// Test with an invalid configuration (invalid maximum score)
BOOST_AUTO_TEST_CASE(test_execute_invalid_max_score) {
    std::vector<std::string> players = {"Alice", "Bob"};
    SetUpGame setup(2, 15, players);  // 15 is not a valid score (only 11 or 21)

    Engine engine;

    // Test if an exception is thrown for an invalid maximum score
    Command* command = &setup;
    BOOST_CHECK_THROW(command->execute(&engine), std::invalid_argument);
}

// Test with more player names than the required number of players
BOOST_AUTO_TEST_CASE(test_execute_invalid_players_count) {
    std::vector<std::string> players = {"Alice", "Bob", "Charlie"};
    SetUpGame setup(2, 11, players);  // Only 2 players are expected

    Engine engine;

    // Test if an exception is thrown when the number of player names exceeds the expected count
    Command* command = &setup;
    BOOST_CHECK_THROW(command->execute(&engine), std::invalid_argument);
}

// Test with fewer player names than the required number of players
BOOST_AUTO_TEST_CASE(test_execute_invalid_players_count_too_few) {
    std::vector<std::string> players = {"Alice"};  // Only one name when two are required
    SetUpGame setup(2, 11, players);

    Engine engine;

    // Test if an exception is thrown when the number of player names is less than the required count
    Command* command = &setup;
    BOOST_CHECK_THROW(command->execute(&engine), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

