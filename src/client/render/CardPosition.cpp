// #include "render.h"
// #include "CardPosition.h"
// #include <SFML/Graphics.hpp>

// namespace render
// {

//     // Default constructor initializing position to (0, 0)
//     CardPosition::CardPosition() : x(0.0), y(0.0) {}

//     // Destructor
//     CardPosition::~CardPosition() {}

//     // Method to adjust position by fixed increments
//     void CardPosition::changePos()
//     {
//         x += 5.0; // Increment x-coordinate
//         y += 3.0; // Increment y-coordinate
//     }

//     // Setter for position
//     void CardPosition::setPosition(double newX, double newY)
//     {
//         x = newX;
//         y = newY;
//     }

//     // Getter for x-coordinate
//     double CardPosition::getX()
//     {
//         return x;
//     }

//     // Getter for y-coordinate
//     double CardPosition::getY()
//     {
//         return y;
//     }

//     // Méthode mise à jour pour renvoyer la position d'une carte selon son index
//     void getCardPosition(int index, double cardWidth, double cardHeight, int &x, int &y) {
//         x = static_cast<int>(index * cardWidth);
//         y = static_cast<int>(cardHeight * 0.5);  // Exemple d'un calcul simple pour la hauteur
//     }

//     // Fonction qui affecte la position du tableau (x, y) selon l'index
//     void getBoardPosition(int index, double cardWidth, double cardHeight, int &x, int &y) {
//         x = static_cast<int>(index * cardWidth * 1.5);
//         y = static_cast<int>(cardHeight * 1.2);  // Exemple d'un autre calcul
//     }
// }
