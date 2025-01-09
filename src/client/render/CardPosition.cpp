// CardPosition.cpp
#include "CardPosition.h"
#include <SFML/Graphics.hpp>

namespace render {
    CardPosition::CardPosition() : x(0.0), y(0.0) {}

    CardPosition::~CardPosition() {}

    void CardPosition::changePos() {
        x += 5;
        y += 3;
    }

    void CardPosition::setPosition(double newX, double newY) {
        x = newX;
        y = newY;
    }

    double CardPosition::getX() {
        return x;
    }

    double CardPosition::getY() {
        return y;
    }

    // Méthode mise à jour pour renvoyer la position d'une carte selon son index
    sf::Vector2f CardPosition::getCardPosition(int index, double cardWidth, double cardHeight) {
        double spacing = 15.0;  // Espacement entre les cartes
        double cardPosX = x + (index * (spacing + cardWidth));  // Calcul de la position en X en fonction de l'index
        double cardPosY = y;  // Position Y constante

        return sf::Vector2f(cardPosX, cardPosY);
    }

    sf::Vector2f CardPosition::getBoardPosition(int index, double cardWidth, double cardHeight) {
        // Par exemple, les cartes peuvent être alignées horizontalement
        // ou en forme de grille, donc la position est calculée selon l'index.
        double xPos = x + (index * (cardWidth + 10));  // Ajouter un espace entre les cartes
        double yPos = y;

        return sf::Vector2f(xPos, yPos);
    }
}
