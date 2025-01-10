#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <vector>

#include "../../src/shared/engine.h"
#include "../../src/shared/state.h"
using namespace engine;
using namespace state;

BOOST_AUTO_TEST_SUITE(SetUpGameTests)

// Test with valid configuration (correct number of players and score, no AI)
BOOST_AUTO_TEST_CASE(test_execute_valid) {
    std::vector<std::string> players = {"Alice", "Bob"};
    SetUpGame setup(2, 4, players, 'n', 0); // No AI, level 0

    Engine engine;

    // Test if the execute method works via polymorphism using Command*
    Command* command = &setup;  // Base class pointer
    BOOST_CHECK(command->execute(&engine));  // Polymorphic call to execute
}

// Test with an invalid configuration (incorrect number of players)
BOOST_AUTO_TEST_CASE(test_execute_invalid_number_of_players) {
    std::vector<std::string> players = {"Alice", "Bob", "Charlie"};
    SetUpGame setup(3, 11, players, 'n', 0); // Invalid number of players

    Engine engine;

    // Test if an exception is thrown when the number of players is incorrect
    Command* command = &setup;
    BOOST_CHECK_THROW(command->execute(&engine), std::invalid_argument);
}

// Test with an invalid configuration (invalid maximum score)
BOOST_AUTO_TEST_CASE(test_execute_invalid_max_score) {
    std::vector<std::string> players = {"Alice", "Bob"};
    SetUpGame setup(2, 15, players, 'n', 0); // Invalid max score (only 11 or 21 allowed)

    Engine engine;

    // Test if an exception is thrown for an invalid maximum score
    Command* command = &setup;
    BOOST_CHECK_THROW(command->execute(&engine), std::invalid_argument);
}



// Test with AI player configuration
BOOST_AUTO_TEST_CASE(test_execute_with_ai_player) {
    std::vector<std::string> players = {"Alice","AI"};
    SetUpGame setup(2, 4, players, 'y', 1); // AI is enabled with level 1

    Engine engine;

    // Test if the execute method works with AI configuration
    Command* command = &setup;
    engine.setActualCmd(command);
    BOOST_CHECK(command->execute(&engine));  // Polymorphic call to execute
}

BOOST_AUTO_TEST_SUITE_END()
