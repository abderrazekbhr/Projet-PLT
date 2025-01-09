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
    void getCardPosition(int index, double cardWidth, double cardHeight, int &x, int &y) {
        x = static_cast<int>(index * cardWidth);
        y = static_cast<int>(cardHeight * 0.5);  // Exemple d'un calcul simple pour la hauteur
    }

    // Fonction qui affecte la position du tableau (x, y) selon l'index
    void getBoardPosition(int index, double cardWidth, double cardHeight, int &x, int &y) {
        x = static_cast<int>(index * cardWidth * 1.5);
        y = static_cast<int>(cardHeight * 1.2);  // Exemple d'un autre calcul
    }
}
