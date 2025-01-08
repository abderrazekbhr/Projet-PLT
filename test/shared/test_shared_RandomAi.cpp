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

    // Configuration avec 2 joueurs (nombre valide)
    std::vector<std::string> playerNames = {"Joueur1", "Joueur2"};
    SetUpGame setUpGame(2, 21, playerNames); // 2 joueurs et un score max de 21

    Engine engine;

    if (!setUpGame.execute(&engine)) {
        BOOST_FAIL("La configuration du jeu a échoué.");
    }

    // Récupérer les objets de jeu après initialisation
    GameBoard* board = engine.getState().getBoard();
    Player& player = engine.getActualPlayer();

    Card card1(NumberCard::un, TypeCard::coeur);
    Card card2(NumberCard::deux, TypeCard::coeur);
    Card card3(NumberCard::trois, TypeCard::coeur);

    player.addHoldedCard(card1);
    player.addHoldedCard(card2);
    player.addHoldedCard(card3);

    board->addCardToBoard(card2);
    board->addCardToBoard(card3);

    RandomAi randomAi;

    randomAi.run(engine);

    // Après l'exécution de l'IA, le joueur devrait avoir capturé des cartes ou lancé une carte
    BOOST_CHECK_EQUAL(player.getSizeCollectedCards(), 1); // L'action de capture devrait se produire
}

BOOST_AUTO_TEST_CASE(RandomAiThrowCardTest) {
    // Configuration avec 2 joueurs (nombre valide)
    std::vector<std::string> playerNames = {"Joueur1", "Joueur2"};
    SetUpGame setUpGame(2, 21, playerNames); // 2 joueurs et un score max de 21

    Engine engine;

    if (!setUpGame.execute(&engine)) {
        BOOST_FAIL("La configuration du jeu a échoué.");
    }

    GameBoard* board = engine.getState().getBoard();
    Player& player = engine.getActualPlayer();

    Card card1(NumberCard::un, TypeCard::coeur);
    Card card2(NumberCard::deux, TypeCard::coeur);

    player.addHoldedCard(card1);
    player.addHoldedCard(card2);

    board->addCardToBoard(card2);

    RandomAi randomAi;

    randomAi.run(engine);

    // Après l'exécution de l'IA, le joueur devrait avoir lancé une carte si aucune capture n'est possible
    BOOST_CHECK_EQUAL(player.getSizeHoldedCards(), 1);  // Le joueur doit avoir lancé 1 carte
    BOOST_CHECK_EQUAL(board->getNumberCardBoard(), 3);  // Une carte doit être ajoutée au plateau
}


BOOST_AUTO_TEST_SUITE_END()
