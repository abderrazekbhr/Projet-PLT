#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>
#include "../shared/engine/Engine.h"
#include "../shared/state/GameBoard.h"
#include "../shared/state/Player.h"
#include "../shared/state/Card.h"
#include "../shared/ai/RandomAi.h"
#include "../shared/engine/SetUpGame.h"

using namespace ai;
using namespace engine;
using namespace state;

BOOST_AUTO_TEST_SUITE(RandomAiTestSuite)

BOOST_AUTO_TEST_CASE(RandomAiCaptureCardTest) {
    // Configuration avec 2 joueurs (1 IA incluse)
    std::vector<std::string> playerNames = {"Joueur1"};
    SetUpGame setUpGame(2, 21, playerNames, 'y', 1); // 2 joueurs, score max 21, 1 IA

    Engine engine;

    if (!setUpGame.execute(&engine)) {
        BOOST_FAIL("La configuration du jeu a échoué.");
    }

    // Récupérer les objets de jeu après initialisation
    GameBoard* board = engine.getState().getBoard();
    Player& player = engine.getActualPlayer();

    // Ajout des cartes à la main du joueur et au plateau
    Card card1(NumberCard::un, TypeCard::coeur);
    Card card2(NumberCard::deux, TypeCard::coeur);
    Card card3(NumberCard::trois, TypeCard::coeur);

    player.addHoldedCard(card1);
    player.addHoldedCard(card2);
    board->addCardToBoard(card2);

    RandomAi randomAi;
    randomAi.run(engine);

    // Vérifications après exécution de l'IA
    BOOST_CHECK_EQUAL(player.getSizeCollectedCards(), 1); // Une carte capturée
    BOOST_CHECK_EQUAL(player.getSizeHoldedCards(), 1);    // Une carte restante
    BOOST_CHECK_EQUAL(board->getNumberCardBoard(), 0);    // Le plateau est vide
}

BOOST_AUTO_TEST_CASE(RandomAiThrowCardTest) {
    // Configuration avec 2 joueurs (aucune IA)
    std::vector<std::string> playerNames = {"Joueur1", "Joueur2"};
    SetUpGame setUpGame(2, 21, playerNames, 'n', 0); // 2 joueurs, score max 21, pas d'IA

    Engine engine;

    if (!setUpGame.execute(&engine)) {
        BOOST_FAIL("La configuration du jeu a échoué.");
    }

    GameBoard* board = engine.getState().getBoard();
    Player& player = engine.getActualPlayer();

    // Ajout des cartes à la main du joueur
    Card card1(NumberCard::un, TypeCard::coeur);
    Card card2(NumberCard::deux, TypeCard::coeur);

    player.addHoldedCard(card1);
    player.addHoldedCard(card2);

    RandomAi randomAi;
    randomAi.run(engine);

    // Vérifications après exécution de l'IA
    BOOST_CHECK_EQUAL(player.getSizeHoldedCards(), 1);  // Une carte restante
    BOOST_CHECK_EQUAL(board->getNumberCardBoard(), 1); // Une carte ajoutée au plateau
}

BOOST_AUTO_TEST_SUITE_END()
