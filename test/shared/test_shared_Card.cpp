#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace state;

BOOST_AUTO_TEST_SUITE(CardTests)

BOOST_AUTO_TEST_CASE(test_card_creation) {
    // Création de la carte avec un nombre et un type
    Card card(NumberCard::un, TypeCard::coeur);

    // Vérifie que le numéro de la carte est bien égal à ONE
    BOOST_CHECK_EQUAL(card.getNumberCard(), NumberCard::un);

    // Vérifie que le type de la carte est bien égal à HEART
    BOOST_CHECK_EQUAL(card.getTypeCard(), TypeCard::coeur);
}

BOOST_AUTO_TEST_CASE(test_card_equals_same_card) {
    // Création de deux cartes identiques
    Card card1(NumberCard::cinq, TypeCard::carreau);
    Card card2(NumberCard::cinq, TypeCard::carreau);

    // Vérifie que les deux cartes sont égales
    BOOST_CHECK(card1.equals(card2));
}

BOOST_AUTO_TEST_CASE(test_card_equals_different_card) {
    // Création de deux cartes différentes
    Card card1(NumberCard::cinq, TypeCard::carreau);
    Card card2(NumberCard::roi, TypeCard::coeur);

    // Vérifie que les deux cartes ne sont pas égales
    BOOST_CHECK(!card1.equals(card2));
}

BOOST_AUTO_TEST_SUITE_END()
