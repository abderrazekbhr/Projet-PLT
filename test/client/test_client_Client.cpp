#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <sstream>
#include "client.h"

using namespace std;
using namespace client;

BOOST_AUTO_TEST_SUITE(Client_test);

// Helper function to mock input and output
void mockIO(const std::string& input, std::string& output, const std::function<void()>& testFunction) {
    std::stringstream inputStream(input);
    std::stringstream outputStream;
    std::streambuf* cinBackup = std::cin.rdbuf();
    std::streambuf* coutBackup = std::cout.rdbuf();

    std::cin.rdbuf(inputStream.rdbuf());
    std::cout.rdbuf(outputStream.rdbuf());

    testFunction();

    std::cin.rdbuf(cinBackup);
    std::cout.rdbuf(coutBackup);
    output = outputStream.str();
}

BOOST_AUTO_TEST_CASE(setUp_test) {
    std::string output;
    mockIO("2\n11\nAlice\nBob\n", output, []() {
        Client c;
        c.setUp();
    });
    BOOST_CHECK(output.find("Enter number of players (2-4): ") != std::string::npos);
    BOOST_CHECK(output.find("Enter maximum score (11 or 22): ") != std::string::npos);
    BOOST_CHECK(output.find("Enter player 1 name: ") != std::string::npos);
    BOOST_CHECK(output.find("Enter player 2 name: ") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(initDistribute_test) {
    std::string output;
    mockIO("y\n", output, []() {
        Client c;
        BOOST_CHECK(c.initDistribute());
    });
    BOOST_CHECK(output.find("Do you want to distribute the cards? (y/n): ") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(distributeCard_test) {
    std::string output;
    mockIO("", output, []() {
        Client c;
        c.distributeCard();
    });
    BOOST_CHECK(output.empty()); // No user interaction, should only call engine.runCommand
}

BOOST_AUTO_TEST_CASE(chooseAction_test) {
    std::string output;
    mockIO("1\n", output, []() {
        Client c;
        ActionType action = c.chooseAction();
        BOOST_CHECK(action == Throwing);
    });
    BOOST_CHECK(output.find("Choose an action: 1. Throw card 2. Capture card") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(playThrowCard_test) {
    std::string output;
    mockIO("0\n", output, []() {
        Client c;
        c.playThrowCard();
    });
    BOOST_CHECK(output.find("Enter the index of the card to throw: ") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(playCaptureCard_test) {
    std::string output;
    mockIO("0\n0\nn\n", output, []() {
        Client c;
        c.playCaptureCard();
    });
    BOOST_CHECK(output.find("Enter the index of the card to throw: ") != std::string::npos);
    BOOST_CHECK(output.find("Enter the index of the card to collect: ") != std::string::npos);
    BOOST_CHECK(output.find("Do you want to collect another card? (y/n): ") != std::string::npos);
}

// BOOST_AUTO_TEST_CASE(destructor_test) {
//     BOOST_CHECK_NO_THROW({
//         Client c;
//     });
// }

BOOST_AUTO_TEST_SUITE_END();
