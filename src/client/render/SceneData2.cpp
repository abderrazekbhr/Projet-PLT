#include "SceneData.h"
#include <SFML/Graphics.hpp>
#include "CardPosition.h"
#include "SceneComponent.h"

namespace render {

CardPosition SceneData::cardPos; // Définition de l'attribut statique cardPos

// Constructeur : Initialise les attributs du plateau, la police et les dimensions des cartes
SceneData::SceneData() : bordWidth(800.0), boardHeight(600.0), cardWidth(50.0), cardHeight(70.0) {
    // Chargement de la police depuis un fichier (nécessaire pour afficher du texte SFML)
    if (!font.loadFromFile("resources/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    // Initialisation du plateau (RectangleShape) avec une taille et une couleur de base
    board.setSize(sf::Vector2f(bordWidth, boardHeight));
    board.setFillColor(sf::Color::Green);
    board.setPosition(100.0f, 100.0f); //Position initiale du plateau
}

// Destructeur
SceneData::~SceneData() {}

// Initialise la scène en fonction de l'ID de la composante (ex: MENU, PLAYER_A)
void SceneData::init(sf::RenderWindow& window, SceneComponent& id) {
    if (id == SceneComponent::MENU) {
        board.setFillColor(sf::Color::Blue); // Change la couleur pour indiquer le MENU
    }
    // D'autres initialisations peuvent être ajoutées selon le type de scène
}

// Met à jour les données de la scène en fonction des informations du joueur et du tour
void SceneData::update(state::Player& playerInfo, int turn) {
    // Création d'un texte pour afficher le score d'un joueur
    sf::Text playerScoreText;
    playerScoreText.setFont(font);
    playerScoreText.setString("Score: " + std::to_string(playerInfo.getScore()));
    playerScoreText.setCharacterSize(24);
    playerScoreText.setFillColor(sf::Color::White);

    // Positionne chaque texte légèrement en dessous de l'autre en fonction du tour
    playerScoreText.setPosition(10.0f, 10.0f + turn * 30.0f);
    text.push_back(playerScoreText); // Ajoute le texte à la liste des textes
}

// Dessine les éléments de la scène dans la fenêtre
void SceneData::drawSceneData(sf::RenderWindow& window) {
    window.draw(board); // Dessine le plateau

    // Dessine toutes les cartes
    for (const auto& card : cards) {
        window.draw(card);
    }

    // Dessine le texte (score, infos, etc.)
    for (const auto& t : text) {
        window.draw(t);
    }
}

// Méthode héritée de sf::Drawable pour dessiner les objets de la classe
void SceneData::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Dessin du plateau
    target.draw(board, states);

    // Dessin des cartes
    for (const auto& card : cards) {
        target.draw(card, states);
    }

    // Dessin des textes
    for (const auto& t : text) {
        target.draw(t, states);
    }
}

// Dessine les cartes en main (RectangleShape représentant chaque carte)
void SceneData::drawCardsOnHand(sf::RenderWindow& window) {
    for (const auto& card : cards) {
        window.draw(card); // Affiche chaque carte sur la fenêtre
    }
}

// Dessine les cartes sur le plateau
void SceneData::drawCardsOnBoard(sf::RenderWindow& window) {
    for (const auto& card : cards) {
        window.draw(card); // Dessine chaque carte positionnée sur le plateau
    }
}

// Ajoute des cartes au plateau (elles sont représentées par RectangleShape)
void SceneData::addCardToBoard(std::vector<state::Card> cardsToAdd) {
    for (const auto& c : cardsToAdd) {
        // Création d'une carte (RectangleShape)
        sf::RectangleShape card(sf::Vector2f(cardWidth, cardHeight));
        card.setFillColor(sf::Color::Red); // Couleur pour une carte "plateau"
        card.setPosition(cardPos.getX(), cardPos.getY()); // Utilise cardPos pour positionner

        cards.push_back(card); // Ajoute la carte à la liste
        cardPos.changePos();   // Met à jour la position pour la prochaine carte
    }
}

// Ajoute des cartes à la main du joueur
void SceneData::addCardToHand(std::vector<state::Card> cardsToAdd) {
    for (const auto& c : cardsToAdd) {
        sf::RectangleShape card(sf::Vector2f(cardWidth, cardHeight));
        card.setFillColor(sf::Color::Yellow); // Couleur pour une carte "en main"
        card.setPosition(cardPos.getX(), cardPos.getY());

        cards.push_back(card);
        cardPos.changePos();
    }
}

// Supprime une carte du plateau (simple exemple : supprime la dernière carte ajoutée)
void SceneData::removeCardFromBoard(state::Card card) {
    if (!cards.empty()) {
        cards.pop_back(); // Supprime la dernière carte
    }
}

// Supprime une carte de la main du joueur
void SceneData::removeCardFromHand(state::Card card) {
    if (!cards.empty()) {
        cards.pop_back(); // Supprime la dernière carte en main
    }
}

// Sélectionne une carte de la main à un index donné
state::Card SceneData::selectCardFromHand(int cardIndex) {
    // Retourne une carte factice (à adapter selon l'implémentation)
    return state::Card();
}

// Sélectionne des cartes du plateau en fonction de plusieurs indices
std::vector<state::Card> SceneData::selectCardFromBoard(std::vector<int> cardIndexes) {
    // Retourne un vecteur de cartes factices (à adapter selon l'implémentation)
    return std::vector<state::Card>();
}

}
