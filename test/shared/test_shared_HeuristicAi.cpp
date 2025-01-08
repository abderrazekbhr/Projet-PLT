#include <boost/test/unit_test.hpp>
#include "../../src/shared/ai.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/state.h"
#include <vector>
#include <map>

using namespace ai;
using namespace state;
using namespace engine;

BOOST_AUTO_TEST_CASE(test_heuristic_ai)
{
    // Initialisation de l'état et de l'IA
    Engine e; // Constructeur simple
    State &state = e.getState();
    HeuristicAi ai("Heuristic AI");

    // Création de joueurs et configuration du jeu
    state.addPlayer("Player 1");
    state.addPlayer("Player 2");
    state.setMaxScore(11);
    state.setNbPlayer(2);

    Player *player1 = state.getAllPlayers()[0];
    Player *player2 = state.getAllPlayers()[1];

    // Simulation de cartes dans la main du joueur et sur le plateau
    std::vector<Card> hand = {
        Card(sept, carreau),  // Sept Dinari
        Card(trois, pique),
        Card(cinq, coeur)
    };
    std::vector<Card> board = {
        Card(deux, treffle),
        Card(cinq, carreau),
        Card(sept, pique)
    };

    // Ajouter les cartes dans la main du joueur
    for (auto &card : hand) {
        player1->addHoldedCard(card);
    }

    // Ajouter les cartes sur le plateau
    for (auto &card : board) {
        state.getBoard()->addCardToBoard(card);
    }

    // Test de checkPossibleChkoba
    auto chkobaResult = ai.checkPossibleChkoba(hand, board);
    BOOST_CHECK_EQUAL(chkobaResult.size(), 0); // Pas de Chkobba possible ici

    // Test de checkPossible7Carreau
    auto septCarreauResult = ai.checkPossible7Carreau(hand, board);
    BOOST_CHECK(septCarreauResult["hand"].size() > 0);
    BOOST_CHECK(septCarreauResult["board"].size() > 0);

    // Vérification des indices
    BOOST_CHECK_EQUAL(septCarreauResult["hand"][0], 0); // Sept Dinari dans la main
    BOOST_CHECK_EQUAL(septCarreauResult["board"][0], 1); // Sept Dinari sur le plateau

    // Test de maximiseProfit
    auto bestMove = ai.maximiseProfit(hand, board);
    BOOST_CHECK(bestMove["hand"].size() > 0);
    BOOST_CHECK(bestMove["board"].size() > 0);

    // Vérification des scores maximaux
    int expectedHandIndex = 0; // Sept Dinari maximise souvent les points
    BOOST_CHECK_EQUAL(bestMove["hand"][0], expectedHandIndex);

    // Test de throwStrategy
    int cardToThrow = ai.throwStrategy(hand);
    BOOST_CHECK_EQUAL(cardToThrow, 1); // La carte avec le plus petit nombre est choisie

    // Test du run
    BOOST_CHECK_NO_THROW(ai.run(&e)); // Exécution complète de l'IA sans erreur
}
