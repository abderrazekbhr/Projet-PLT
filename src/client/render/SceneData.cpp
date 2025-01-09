#include "SceneData.h"
#include "state/Player.h"
#include "state/Card.h"
#include <SFML/Graphics.hpp>

namespace render {

    // Constructeur de la classe SceneData
    SceneData::SceneData()
        : bordWidth(800), boardHeight(600), cardWidth(80)
    {}

    // Destructeur de la classe SceneData
    SceneData::~SceneData() = default;

    // Initialisation de la scène, chargement de la police, et paramétrage du plateau
    void SceneData::init(sf::RenderWindow& window, SceneComponent& id) {
        // Charger la police pour le texte (assurez-vous que le fichier "arial.ttf" existe dans votre dossier de projet)
        /*font.loadFromFile("arial.ttf");
        board.setSize(sf::Vector2f(bordWidth, boardHeight)); // Définir la taille du plateau
        board.setFillColor(sf::Color(200, 200, 255)); // Couleur du plateau

        // Position initiale des cartes sur le plateau et les mains (ajuster selon le jeu)
        cardPos = CardPosition();  // Position des cartes (l'objet CardPosition peut gérer la position sur le plateau)*/
    }

    // Mise à jour de la scène, par exemple, pour mettre à jour le score et les informations de la carte
    void SceneData::update(state::Player& playerInfo, int turn) {
        // Logique pour gérer l'actualisation des informations sur le joueur et du score
        // Ex: Mettre à jour le score à chaque tour ou ajouter des actions spécifiques du joueur
        text.clear(); // Vider le texte précédent

        // Affichage du nom et du score du joueur
        sf::Text playerText;
        playerText.setFont(font);
        playerText.setString("Player: " + playerInfo.getName() + " - Score: " + std::to_string(playerInfo.getScore()));
        playerText.setCharacterSize(20);
        playerText.setFillColor(sf::Color::Black);
        playerText.setPosition(10, 10); // Positionner le texte
        text.push_back(playerText); // Ajouter le texte à la liste pour l'afficher

        // Vous pouvez aussi mettre à jour d'autres éléments ici en fonction du tour
    }

    // Dessiner la scène entière, incluant le plateau, les cartes sur la main et les cartes sur le plateau
    void SceneData::drawSceneData(sf::RenderWindow& window, state::Player& player) {
        window.clear(); // Effacer l'écran

        // Dessiner le plateau de jeu
        window.draw(board);

        // Dessiner les cartes sur la main du joueur
        drawCardsOnHand(window, player);  // Passer l'instance player ici

        // Dessiner les cartes sur le plateau de jeu
        drawCardsOnBoard(window, player);

        // Afficher le texte sur le score du joueur
        for (const auto& t : text) {
            window.draw(t);
        }
    }

    // Dessiner les cartes sur la main du joueur
    void SceneData::drawCardsOnHand(sf::RenderWindow& window, state::Player& player)  {
        // Récupérer les cartes en main du joueur
        std::vector<state::Card> heldCards = player.getHoldCard();  // Utiliser l'instance player ici
        int size = heldCards.size();
        for (int i = 0; i < size; ++i) {
            state::Card card = heldCards[i];

            // Création d'un rectangle pour la carte
            sf::RectangleShape cardShape(sf::Vector2f(cardWidth, cardHeight));
            cardShape.setPosition(sf::Vector2f(50 + i * (cardWidth + 10), boardHeight - cardHeight - 20)); // Positionner les cartes

            // Définir la couleur de la carte en fonction du type
            switch (card.getTypeCard()) {
            case state::TypeCard::coeur: cardShape.setFillColor(sf::Color::Red); break;
            case state::TypeCard::carreau: cardShape.setFillColor(sf::Color::Yellow); break;
            case state::TypeCard::pique: cardShape.setFillColor(sf::Color::Green); break;
            case state::TypeCard::treffle: cardShape.setFillColor(sf::Color::Blue); break;
            }

            // Ajouter un cadre plus foncé si la carte est sélectionnée
            if (i == selectedCardIndex) {
                cardShape.setOutlineColor(sf::Color::Black);  // Bordure noire
                cardShape.setOutlineThickness(5);  // Épaisseur de la bordure (plus gros, donc "gras")
            } else {
                cardShape.setOutlineColor(sf::Color::Transparent);  // Pas de bordure si non sélectionnée
                cardShape.setOutlineThickness(1);  // Taille normale de la bordure
            }

            window.draw(cardShape);  // Dessiner la carte sur la main
        }
    }


    void render::SceneData::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // Exemple : Dessiner le plateau et les cartes graphiques
        target.draw(board, states); // Dessine le plateau

        // Dessiner toutes les cartes sur le plateau
        for (const auto& cardShape : boardCardShapes) {
            target.draw(cardShape, states);
        }

        // Dessiner toutes les cartes dans la main
        for (const auto& handShape : handCardShapes) {
            target.draw(handShape, states);
        }

        // Dessiner le texte associé (si besoin)
        for (const auto& txt : text) {
            target.draw(txt, states);
        }
    }
    // Dessiner les cartes sur le plateau
    void SceneData::drawCardsOnBoard(sf::RenderWindow& window , state::Player& player) {
        std::vector<state::Card> collectedCards = player.getCollectCard(); // Récupérer les cartes sur le plateau

        for (size_t i = 0; i < collectedCards.size(); ++i) {
            state::Card card = collectedCards[i];

            // Création d'un rectangle pour la carte
            sf::RectangleShape cardShape(sf::Vector2f(cardWidth, cardHeight));
            cardShape.setPosition(sf::Vector2f(50 + i * (cardWidth + 10), 50));  // Positionner sur le plateau

            // Définir la couleur de la carte en fonction du type
            switch (card.getTypeCard()) {
            case state::TypeCard::coeur: cardShape.setFillColor(sf::Color::Red); break;
            case state::TypeCard::carreau: cardShape.setFillColor(sf::Color::Yellow); break;
            case state::TypeCard::pique: cardShape.setFillColor(sf::Color::Green); break;
            case state::TypeCard::treffle: cardShape.setFillColor(sf::Color::Blue); break;
            }

            // Ajouter un cadre plus foncé si la carte est sélectionnée
            if (std::find(selectedBoardCards.begin(), selectedBoardCards.end(), i) != selectedBoardCards.end()) {
                cardShape.setOutlineColor(sf::Color::Black);  // Bordure noire
                cardShape.setOutlineThickness(5);  // Épaisseur de la bordure (plus gros, donc "gras")
            } else {
                cardShape.setOutlineColor(sf::Color::Transparent);  // Pas de bordure si non sélectionnée
                cardShape.setOutlineThickness(1);  // Taille normale de la bordure
            }

            window.draw(cardShape);  // Dessiner la carte sur le plateau
        }
    }

    // Ajouter une carte au plateau de jeu et la dessiner graphiquement
    void SceneData::addCardToBoard( state::Card& card) {
        // Ajouter la carte à la liste des cartes sur le plateau
        boardCards.push_back(card);

        // Créer un rectangle qui représentera graphiquement la carte sur le plateau
        sf::RectangleShape cardShape(sf::Vector2f(cardWidth, cardHeight));

        // Définir la couleur de la carte en fonction de son type
        switch (card.getTypeCard()) {
        case state::TypeCard::coeur:
            cardShape.setFillColor(sf::Color::Red);
            break;
        case state::TypeCard::carreau:
            cardShape.setFillColor(sf::Color::Yellow);
            break;
        case state::TypeCard::pique:
            cardShape.setFillColor(sf::Color::Green);
            break;
        case state::TypeCard::treffle:
            cardShape.setFillColor(sf::Color::Blue);
            break;
        }

        // Définir la position de la carte sur le plateau
        // Exemple de positionnement : afficher les cartes horizontalement avec un décalage
        float xPos = 50 + (boardCards.size() - 1) * (cardWidth + 10);
        float yPos = 50;  // Définir la position Y fixe pour les cartes

        cardShape.setPosition(sf::Vector2f(xPos, yPos)); // Positionner la carte

        // Ajouter la forme graphique de la carte dans une liste de cartes sur le plateau pour dessin
        boardCardShapes.push_back(cardShape);
    }

    // Ajouter une carte à la main du joueur, à la fois logiquement et graphiquement
    void SceneData::addCardToHand(state::Card& card) {
        // Créer la forme graphique pour la carte (rectangle représentant la carte)
        sf::RectangleShape cardShape(sf::Vector2f(cardWidth, cardHeight));

        // Positionner la carte graphiquement dans la main du joueur
        float xPosition = 50 + handCardShapes.size() * (cardWidth + 10); // Position horizontale, espacement entre les cartes
        float yPosition = boardHeight - cardHeight - 20;  // Position verticale fixée juste au-dessus du bas du plateau
        cardShape.setPosition(sf::Vector2f(xPosition, yPosition));

        // Définir la couleur de la carte selon son type
        switch (card.getTypeCard()) {
        case state::TypeCard::coeur:
            cardShape.setFillColor(sf::Color::Red);  // Cœur
            break;
        case state::TypeCard::carreau:
            cardShape.setFillColor(sf::Color::Yellow);  // Carreau
            break;
        case state::TypeCard::pique:
            cardShape.setFillColor(sf::Color::Green);  // Pique
            break;
        case state::TypeCard::treffle:
            cardShape.setFillColor(sf::Color::Blue);  // Trèfle
            break;
        }

        // Ajouter la carte graphique au vecteur `handCardShapes` pour l'affichage
        handCardShapes.push_back(cardShape);  // Ajoute la forme graphique de la carte au vecteur
    }



    // Retirer une carte du plateau
    void SceneData::removeCardFromBoard(state::Card& card) {
        // Chercher et supprimer la carte logique dans boardCards
        auto it = std::find_if(boardCards.begin(), boardCards.end(),
                               [&card]( state::Card& c) { return c.equals(card); });
        if (it != boardCards.end()) {
            // Retirer la carte de la collection logique
            boardCards.erase(it);
        }

        // Chercher et supprimer la carte graphique dans boardCardShapes
        for (size_t i = 0; i < boardCards.size(); ++i) {
            if (boardCards[i].equals(card)) {
                // La carte graphique correspond à l'index de la carte logique
                boardCardShapes.erase(boardCardShapes.begin() + i);  // Supprimer la carte graphique
                break;
            }
        }
    }



    void SceneData::removeCardFromHand(state::Card& card) {
        // Chercher et supprimer la carte logique et sa carte graphique correspondante
       /* auto it = std::find_if(handCardShapes.begin(), handCardShapes.end(),
                               [&card]( std::pair<sf::RectangleShape, state::Card>& p) {
                                   return p.second.equals(card);  // Comparer la carte logique
                               });

        if (it != handCardShapes.end()) {
            // Retirer la carte graphique et la carte logique
            handCardShapes.erase(it);
        }*/
    }



    // Sélectionner une carte de la main du joueur en fonction de son index
    void SceneData::selectCardFromHand(int cardIndex) {
        int size =handCardShapes.size();
        if (cardIndex >= 0 && cardIndex < size) {
            selectedCardIndex = cardIndex;  // Marquer l'index de la carte sélectionnée
        } else {
            selectedCardIndex = -1;  // Aucune carte sélectionnée si l'index est invalide
        }
    }


    // Sélectionner plusieurs cartes sur le plateau de jeu
    void SceneData::selectCardsFromBoard( std::vector<int>& cardIndexes) {
        selectedBoardCards.clear();  // Réinitialiser les cartes sélectionnées précédemment

        // Ajouter les indices des cartes sélectionnées
        for (int idx : cardIndexes) {
            int size =boardCardShapes.size();
            if (idx >= 0 && idx < size) {
                selectedBoardCards.push_back(idx);  // Ajouter l'index de la carte sélectionnée
            }
        }
    }

    void SceneData::setSelectedCardIndex(int index){ selectedCardIndex = index; }

    // Getter pour l'index de la carte sélectionnée
    int SceneData::getSelectedCardIndex(){ return selectedCardIndex; }


}
