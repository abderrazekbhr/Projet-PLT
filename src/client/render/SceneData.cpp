#include "SceneData.h"
#include "state.h"
#include <algorithm> // for std::find

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

    void SceneData::update(state::Player &playerInfo, int turn) {
        text.clear();

        sf::Text playerText;
        playerText.setFont(font);
        playerText.setString("Player: " + playerInfo.getName() + " - Score: " + std::to_string(playerInfo.getScore()));
        playerText.setCharacterSize(20);
        playerText.setFillColor(sf::Color::Black);
        playerText.setPosition(10, 10);

        text.push_back(playerText);
    }

    void SceneData::drawSceneData(sf::RenderWindow &window, state::Player &player) {
        window.clear();
        window.draw(board);

        drawCardsOnHand(window, player);
        drawCardsOnBoard(window, player);

        for (auto &t : text) {
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
            cardShape.setPosition(50 + i * (cardWidth + 10), boardHeight - cardHeight - 20);

            switch (heldCards[i].getTypeCard()) {
                case state::TypeCard::coeur: cardShape.setFillColor(sf::Color::Red); break;
                case state::TypeCard::carreau: cardShape.setFillColor(sf::Color::Yellow); break;
                case state::TypeCard::pique: cardShape.setFillColor(sf::Color::Green); break;
                case state::TypeCard::treffle: cardShape.setFillColor(sf::Color::Blue); break;
            }

            if ((int ) i == selectedCardIndex) {
                cardShape.setOutlineColor(sf::Color::Black);
                cardShape.setOutlineThickness(5);
            } else {
                cardShape.setOutlineColor(sf::Color::Transparent);
            }

            window.draw(cardShape);
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
            sf::RectangleShape cardShape(sf::Vector2f(cardWidth, cardHeight));
            cardShape.setPosition(50 + i * (cardWidth + 10), 50);

            switch (collectedCards[i].getTypeCard()) {
                case state::TypeCard::coeur: cardShape.setFillColor(sf::Color::Red); break;
                case state::TypeCard::carreau: cardShape.setFillColor(sf::Color::Yellow); break;
                case state::TypeCard::pique: cardShape.setFillColor(sf::Color::Green); break;
                case state::TypeCard::treffle: cardShape.setFillColor(sf::Color::Blue); break;
            }

            if (std::find(selectedBoardCards.begin(), selectedBoardCards.end(), i) != selectedBoardCards.end()) {
                cardShape.setOutlineColor(sf::Color::Black);
                cardShape.setOutlineThickness(5);
            } else {
                cardShape.setOutlineColor(sf::Color::Transparent);
            }

            window.draw(cardShape);
        }
    }

    void SceneData::addCardToBoard(state::Card &card) {
        boardCards.push_back(card);
    }

    void SceneData::addCardToHand(state::Card &card) {
        boardCards.push_back(card);
    }

    void SceneData::removeCardFromBoard(state::Card &card) {
        auto it = std::find_if(boardCards.begin(), boardCards.end(), [&card](state::Card &c) { return c.equals(card); });
        if (it != boardCards.end()) {
            boardCards.erase(it);
        }
    }

    void SceneData::removeCardFromHand(state::Card &card) {
        auto it = std::find_if(boardCards.begin(), boardCards.end(), [&card](state::Card &c) { return c.equals(card); });
        if (it != boardCards.end()) {
            boardCards.erase(it);
        }
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

    void SceneData::setSelectedCardIndex(int index) {
        selectedCardIndex = index;
    }

    int SceneData::getSelectedCardIndex() {
        return selectedCardIndex;
    }

} // namespace render
