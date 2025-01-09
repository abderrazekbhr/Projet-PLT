// #include <boost/test/unit_test.hpp>
// #include "../../src/shared/ai.h"
// #include "../../src/shared/engine.h"
// #include "../../src/shared/state.h"
// #include <vector>
// #include <map>

// using namespace ai;
// using namespace state;
// using namespace engine;

// BOOST_AUTO_TEST_CASE(test_heuristic_ai)
// {
//     // Set up the game with 2 players, including 1 AI player.
//     std::vector<std::string> playerNames = {"Player1", "Heurist AI"}; // Names for the players
//     SetUpGame *setUpGame = new SetUpGame(2, 11, playerNames, 'y', 2); // 2 players, max score 21, 2 AI

//     Engine engine;                  // Create an engine to run the game
//     engine.setActualCmd(setUpGame); // Set the game setup as the current command in the engine

//     // Check if the game setup executed successfully. If not, fail the test.
//     if (!setUpGame->execute(&engine))
//     {
//         BOOST_FAIL("Game setup failed.");
//     }

//     // Retrieve all players from the engine's state
//     std::vector<Player *> players = engine.getState().getAllPlayers();
//     std::cout << "Number of players: " << players.size() << std::endl; // Print number of players

//     // Attempt to cast the second player to a RandomAi object.
//     RandomAi *randomAi = dynamic_cast<RandomAi *>(players[1]);
//     if (!randomAi) // If cast fails, report the failure
//     {
//         BOOST_FAIL("Failed to cast Player to RandomAi.");
//     }

//     // Execute the RandomAI logic for the first time (AI makes its move).
//     randomAi->run(&engine);

//     // Add a card to the board and check the card holding logic for RandomAi
//     GameBoard *board = engine.getState().getBoard();                  // Get the game board
//     board->addCardToBoard(Card(NumberCard::deux, TypeCard::treffle)); // Add a card to the board
//     Card card(NumberCard::deux, TypeCard::coeur);                     // Create a new card to be added to RandomAi's hand
//     players[0]->addHoldCard(Card(NumberCard::un, TypeCard::coeur));   // Add a card to Player1's hand

//     // Simulation de cartes dans la main du joueur et sur le plateau
//     std::vector<Card> hand = {
//         Card(sept, carreau), // Sept Dinari
//         Card(trois, pique),
//         Card(cinq, coeur)};
//     std::vector<Card> board = {
//         Card(deux, treffle),
//         Card(cinq, carreau),
//         Card(sept, pique)};

//     // Ajouter les cartes dans la main du joueur
//     for (auto &card : hand)
//     {
//         player1->addHoldedCard(card);
//     }

//     // Ajouter les cartes sur le plateau
//     for (auto &card : board)
//     {
//         state.getBoard()->addCardToBoard(card);
//     }

//     // Test de checkPossibleChkoba
//     auto chkobaResult = ai.checkPossibleChkoba(hand, board);
//     BOOST_CHECK_EQUAL(chkobaResult.size(), 0); // Pas de Chkobba possible ici

//     // Test de checkPossible7Carreau
//     auto septCarreauResult = ai.checkPossible7Carreau(hand, board);
//     BOOST_CHECK(septCarreauResult["hand"].size() > 0);
//     BOOST_CHECK(septCarreauResult["board"].size() > 0);

//     // Vérification des indices
//     BOOST_CHECK_EQUAL(septCarreauResult["hand"][0], 0);  // Sept Dinari dans la main
//     BOOST_CHECK_EQUAL(septCarreauResult["board"][0], 1); // Sept Dinari sur le plateau

//     // Test de maximiseProfit
//     auto bestMove = ai.maximiseProfit(hand, board);
//     BOOST_CHECK(bestMove["hand"].size() > 0);
//     BOOST_CHECK(bestMove["board"].size() > 0);

//     // Vérification des scores maximaux
//     int expectedHandIndex = 0; // Sept Dinari maximise souvent les points
//     BOOST_CHECK_EQUAL(bestMove["hand"][0], expectedHandIndex);

//     // Test de throwStrategy
//     int cardToThrow = ai.throwStrategy(hand);
//     BOOST_CHECK_EQUAL(cardToThrow, 1); // La carte avec le plus petit nombre est choisie

//     // Test du run
//     BOOST_CHECK_NO_THROW(ai.run(&e)); // Exécution complète de l'IA sans erreur
// }

// #include <boost/test/unit_test.hpp>
// #include "engine.h"
// #include "state.h"
// #include "ai.h"

// using namespace ai;
// using namespace engine;
// using namespace state;

// BOOST_AUTO_TEST_SUITE(RandomAiTestSuite)

// // Test case for RandomAi capturing a card
// BOOST_AUTO_TEST_CASE(RandomAiCaptureCardTest)
// {
//     // Set up the game with 2 players, including 1 AI player.
//     std::vector<std::string> playerNames = {"Player1", "Heurist AI"}; // Names for the players
//     SetUpGame *setUpGame = new SetUpGame(2, 11, playerNames, 'y', 2); // 2 players, max score 21, 2 AI

//     Engine engine;                  // Create an engine to run the game
//     engine.setActualCmd(setUpGame); // Set the game setup as the current command in the engine

//     // Check if the game setup executed successfully. If not, fail the test.
//     if (!setUpGame->execute(&engine))
//     {
//         BOOST_FAIL("Game setup failed.");
//     }

//     // Retrieve all players from the engine's state
//     std::vector<Player *> players = engine.getState().getAllPlayers();
//     std::cout << "Number of players: " << players.size() << std::endl; // Print number of players

//     // Attempt to cast the second player to a RandomAi object.
//     RandomAi *randomAi = dynamic_cast<RandomAi *>(players[1]);
//     if (!randomAi) // If cast fails, report the failure
//     {
//         BOOST_FAIL("Failed to cast Player to RandomAi.");
//     }

//     // Execute the RandomAI logic for the first time (AI makes its move).
//     randomAi->run(&engine);

//     // Add a card to the board and check the card holding logic for RandomAi
//     GameBoard *board = engine.getState().getBoard();                  // Get the game board
//     board->addCardToBoard(Card(NumberCard::deux, TypeCard::treffle)); // Add a card to the board
//     Card card(NumberCard::deux, TypeCard::coeur);                     // Create a new card to be added to RandomAi's hand
//     players[0]->addHoldCard(Card(NumberCard::un, TypeCard::coeur));   // Add a card to Player1's hand

//     // Create a throw card action for Player1
//     ThrowCard throwCard(0);
//     engine.setActualCmd(&throwCard); // Set this throw action as the current command

//     throwCard.execute(&engine); // Execute the throw card action

//     // Add the created card to RandomAi's hand
//     randomAi->addHoldedCard(card);

//     // Check if RandomAi's hand now contains one card
//     BOOST_CHECK_EQUAL(randomAi->getSizeHoldedCards(), 1);

//     // Execute the RandomAI logic again (AI should make another move)
//     randomAi->run(&engine);
//     std::cout << "nb=" << randomAi->getHoldCard().size() << std::endl; // Output number of cards in RandomAi's hand

//     // Verify the state after RandomAI's execution
//     BOOST_CHECK_EQUAL(randomAi->getHoldCard().size(), 0); // After running, RandomAi's hand should be empty
//     BOOST_CHECK_EQUAL(board->getNumberCardBoard(), 1);    // The board should have 1 card after RandomAi's move

//     // Add a new card to Player1's hand and RandomAi's hand for further testing
//     players[0]->addHoldCard(Card(NumberCard::trois, TypeCard::coeur)); // Add card to Player1
//     randomAi->addHoldCard(Card(NumberCard::valet, TypeCard::coeur));   // Add card to RandomAi

//     // Create and execute a second throw action for Player1
//     ThrowCard throwCard2(0);
//     engine.setActualCmd(&throwCard2); // Set this throw action as the current command
//     throwCard2.execute(&engine);      // Execute the throw action

//     // RandomAi makes another move
//     randomAi->run(&engine);

//     // Check that RandomAi's hand is empty after the move
//     BOOST_CHECK_EQUAL(randomAi->getSizeHoldedCards(), 0); // RandomAi's hand should be empty
//     BOOST_CHECK_EQUAL(board->getNumberCardBoard(), 3);    // The board should have 3 cards after RandomAi's move
// }

// // End of test suite
// BOOST_AUTO_TEST_SUITE_END()
