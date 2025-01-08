// #include "SceneData.h"
// #include <iostream>
// #include <state/Player.h>

// using namespace render;
// using namespace state;
// using namespace sf;

// // Initialisation de CardPosition
// CardPosition SceneData::cardPos;

// SceneData::SceneData(): bordWidth(800), boardHeight(600), cardWidth(100), cardHeight(150) {
//     // Initialiser le plateau
//     board.setSize(Vector2f(bordWidth, boardHeight));
//     board.setFillColor(Color::Green);
//     board.setPosition(50, 50); // Position du plateau sur la fenêtre

//     // Charger une police par défaut
//     if (!font.loadFromFile("arial.ttf")) {
//         throw std::runtime_error("Failed to load font");
//     }
// }

// SceneData::~SceneData() {}

// // Initialise les composants de la scène
// void SceneData::init(RenderWindow& window, SceneComponent& id) {
//     if (id == MENU) {
//         // Ajouter du texte pour le menu
//         Text menuText("Bienvenue dans le menu", font, 24);
//         menuText.setPosition(100, 100);
//         menuText.setFillColor(Color::White);
//         text.push_back(menuText);
//     }
//     // Autres initialisations basées sur `id` si nécessaire
// }

// // Met à jour la scène en fonction du joueur et du tour
// void SceneData::update(Player& playerInfo, int turn) {
//     // Exemple : Mettre à jour les cartes dans la main du joueur
//     cards.clear();
//     for (const Card& card : playerInfo.getHoldCard()) {
//         RectangleShape cardShape(Vector2f(cardWidth, cardHeight));
//         cardShape.setFillColor(Color::Blue);
//         cardShape.setOutlineThickness(2);
//         cardShape.setOutlineColor(Color::White);
//         cards.push_back(cardShape);
//     }

//     Text playerScoreText;
//     playerScoreText.setFont(font);
//     playerScoreText.setString("Score: " + std::to_string(playerInfo.getScore()));
//     playerScoreText.setCharacterSize(24);
//     playerScoreText.setFillColor(Color::White);

//     // Positionne chaque texte légèrement en dessous de l'autre en fonction du tour
//     playerScoreText.setPosition(10.0f, 10.0f + turn * 30.0f);
//     text.push_back(playerScoreText); // Ajoute le texte à la liste des textes
// }

// // Dessine la scène entière
// void SceneData::drawSceneData(RenderWindow& window) {
//     window.draw(board); // Dessiner le plateau

//     for (auto& card : cards) {
//         window.draw(card); // Dessiner chaque carte
//     }

//     for (auto& txt : text) {
//         window.draw(txt); // Dessiner le texte
//     }
// }

// // Redéfinition de la méthode draw de Drawable
// void SceneData::draw(RenderTarget& target, RenderStates states) {
//     target.draw(board, states);

//     for (auto& card : cards) {
//         target.draw(card, states);
//     }
// }

// // Dessine les cartes dans la main
// void SceneData::drawCardsOnHand(RenderWindow& window) {
//     float xOffset = 50;
//     for (size_t i = 0; i < cards.size(); ++i) {
//         cards[i].setPosition(xOffset + i * (cardWidth + 10), 500); // Ligne en bas
//         window.draw(cards[i]);
//     }
// }

// // Dessine les cartes sur le plateau
// void SceneData::drawCardsOnBoard(RenderWindow& window) {
//     float yOffset = 200;
//     for (size_t i = 0; i < cards.size(); ++i) {
//         cards[i].setPosition(100 + i * (cardWidth + 10), yOffset);
//         window.draw(cards[i]);
//     }
// }

// // Ajoute des cartes au plateau
// void SceneData::addCardToBoard(std::vector<Card> newCards) {
//     for (const auto& card : newCards) {
//         RectangleShape cardShape(Vector2f(cardWidth, cardHeight));
//         cardShape.setFillColor(Color::Red);
//         cardShape.setOutlineThickness(2);
//         cardShape.setOutlineColor(Color::White);
//         cards.push_back(cardShape);
//     }
// }

// // Ajoute des cartes à la main
// void SceneData::addCardToHand(std::vector<Card> newCards) {
//     addCardToBoard(newCards); // Exemple simplifié
// }

// // Retire une carte du plateau
// void SceneData::removeCardFromBoard(Card card) {
//     cards.pop_back(); // Exemple basique
// }

// // Retire une carte de la main
// void SceneData::removeCardFromHand(Card card) {
//     // Implémenter une logique similaire
// }

// // Sélectionne une carte de la main
// Card SceneData::selectCardFromHand(int cardIndex) {
//     // Implémentation fictive : retourner une carte vide
//     return Card(NumberCard::un, TypeCard::coeur); // Exemple
// }

// // Sélectionne des cartes du plateau
// std::vector<Card> SceneData::selectCardFromBoard(std::vector<int> cardIndexes) {
//     std::vector<Card> selectedCards;
//     for (int index : cardIndexes) {
//         // Ajouter une carte fictive comme exemple
//         selectedCards.push_back(Card(NumberCard::un, TypeCard::treffle));
//     }
//     return selectedCards;
// }
