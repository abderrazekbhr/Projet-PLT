#include <boost/test/unit_test.hpp>
#include "engine.h"
#include "state.h"
#include "ai.h"
#include <vector>

using namespace ai;
using namespace engine;
using namespace state;

BOOST_AUTO_TEST_SUITE(AiVsAiTestSuite)

// Test case for Heuristic AI vs Random AI
BOOST_AUTO_TEST_CASE(HeuristicAiVsRandomAiTest)
{
    int heuristicWins = 0;  // Variable to count heuristic AI wins
    int randomWins = 0;     // Variable to count random AI wins
    int numGames = 0; // Number of games to simulate
    int heuristicScore = 0;
    int randomScore = 0;

    // Run the tests for the given number of games
while (numGames< 100){
    // Set up the game with 2 players, both AI players
    std::vector<std::string> playerNames = {"RandomAI_1", "HeuristicAI_1"};
    SetUpGame *setUpGame = new SetUpGame(2, 11, playerNames, 'y', 1); // 2 players, max score 21, 1 AI each

    Engine engine;                  // Create an engine to run the game
    engine.setActualCmd(setUpGame); // Set the game setup as the current command in the engine

    // Check if the game setup executed successfully
    if (!setUpGame->execute(&engine))
    {
        BOOST_FAIL("Game setup failed.");
    }

    // Retrieve all players from the engine's state
    std::vector<Player *> players = engine.getState().getAllPlayers();

    // Cast the players to the appropriate AI types
    HeuristicAi *heuristicAi = dynamic_cast<HeuristicAi *>(players[1]);
    RandomAi *randomAi = dynamic_cast<RandomAi *>(players[0]);

    if (!heuristicAi || !randomAi)
    {
        BOOST_FAIL("Failed to cast players to respective AI types.");
    }

    engine::Command* roundInit = new engine::RoundInitDistributeCards('N'); // Réponse 'N'
    roundInit->execute(&engine);
    engine::RoundDistributeCards roundDistribute;



        for (int i = 0; i < 36; i++) // Iterate through all rounds
        {
            for (int j = 0; j < 3; j++) // Iterate through all turns in a round
            {
                randomAi->run(&engine);
                heuristicAi->run(&engine);

            }
            roundDistribute.execute(&engine);
        }
        // Create a CountScore object
        Command* countScore = new CountScore();  // No need for new, allocated on the stack

        // Execute the CountScore::execute method
        countScore->execute(&engine);

        // Check if any player has exceeded the score limit
         heuristicScore = heuristicScore+heuristicAi->getScore();  // Hypothetical method to get the score
         randomScore = randomScore + randomAi->getScore();        // Hypothetical method to get the score

        BOOST_TEST_MESSAGE("***************************Heuristic AI score: " << heuristicScore );
        BOOST_TEST_MESSAGE("******************************Random AI score: " << randomScore);
        if (heuristicScore >= 11) // Heuristic AI loses
        {
            heuristicWins++;
            heuristicScore =0;
            randomScore =0;
            numGames++;

        }
        else if (randomScore >= 11) // Random AI loses
        {
            randomWins++;
            heuristicScore =0;
            randomScore =0;
            numGames++;

        }
    }


    // After all games, check the results
    BOOST_TEST_MESSAGE("******************************************Heuristic AI wins: " << heuristicWins << " out of " << numGames);
    BOOST_TEST_MESSAGE("*******************************************Random AI wins: " << randomWins << " out of " << numGames);
}
// End of test suite
BOOST_AUTO_TEST_SUITE_END()
