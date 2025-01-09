#include "SceneData.h"
#include "state/Player.h"
#include "state/Card.h"
#include <SFML/Graphics.hpp>

namespace render {

    // Constructor of the SceneData class
    SceneData::SceneData(): bordWidth(800), boardHeight(600), cardWidth(80), cardHeight(120), selectedCardIndex(-1)
    {}

    // Destructor of the SceneData class
    SceneData::~SceneData() {}

    // Initialization of the scene, loading the font, and setting up the board
    void SceneData::init(sf::RenderWindow& window, SceneComponent& id) {
        // Load the font for the text (make sure the file "arial.ttf" exists in your project folder)
        font.loadFromFile("arial.ttf");
        board.setSize(sf::Vector2f(bordWidth, boardHeight)); // Set the size of the board
        board.setFillColor(sf::Color(200, 200, 255)); // Board color

        // Initial position of the cards on the board and hands (adjust according to the game)
        cardPos = CardPosition();  // Card position (the CardPosition object can manage the position on the board)
    }

    // Update the scene, for example, to update the score and card information
    void SceneData::update(state::Player& playerInfo, int turn) {
        // Logic to handle updating player information and score
        // Ex: Update the score each turn or add specific player actions
        text.clear(); // Clear previous text

        // Display the player's name and score
        sf::Text playerText;
        playerText.setFont(font);
        playerText.setString("Player: " + playerInfo.getName() + " - Score: " + std::to_string(playerInfo.getScore()));
        playerText.setCharacterSize(20);
        playerText.setFillColor(sf::Color::Black);
        playerText.setPosition(10, 10); // Position the text
        text.push_back(playerText); // Add the text to the list for display

        // You can also update other elements here depending on the turn
    }

    // Draw the entire scene, including the board, cards in hand, and cards on the board
    void SceneData::drawSceneData(sf::RenderWindow& window, state::Player& player) {
        window.clear(); // Clear the screen

        // Draw the game board
        window.draw(board);

        // Draw the cards in the player's hand
        drawCardsOnHand(window, player);  // Pass the player instance here

        // Draw the cards on the game board
        drawCardsOnBoard(window, player);

        // Display the player's score text
        for (const auto& t : text) {
            window.draw(t);
        }
    }

    // Draw the cards in the player's hand
    void SceneData::drawCardsOnHand(sf::RenderWindow& window, state::Player& player) {
        // Get the cards in the player's hand
        std::vector<state::Card> heldCards = player.getHoldCard();  // Use the player instance here

        for (size_t i = 0; i < heldCards.size(); ++i) {
            state::Card card = heldCards[i];

            // Create a rectangle for the card
            sf::RectangleShape cardShape(sf::Vector2f(cardWidth, cardHeight));
            cardShape.setPosition(sf::Vector2f(50 + i * (cardWidth + 10), boardHeight - cardHeight - 20)); // Position the cards

            // Set the card color based on the type
            switch (card.getTypeCard()) {
            case state::TypeCard::coeur: cardShape.setFillColor(sf::Color::Red); break;
            case state::TypeCard::carreau: cardShape.setFillColor(sf::Color::Yellow); break;
            case state::TypeCard::pique: cardShape.setFillColor(sf::Color::Green); break;
            case state::TypeCard::treffle: cardShape.setFillColor(sf::Color::Blue); break;
            }

            // Add a darker border if the card is selected
            if (i == selectedCardIndex) {
                cardShape.setOutlineColor(sf::Color::Black);  // Black border
                cardShape.setOutlineThickness(5);  // Border thickness (thicker, hence "bold")
            } else {
                cardShape.setOutlineColor(sf::Color::Transparent);  // No border if not selected
                cardShape.setOutlineThickness(1);  // Normal border size
            }

            window.draw(cardShape);  // Draw the card in hand
        }
    }

    // Draw the cards on the board
    void SceneData::drawCardsOnBoard(sf::RenderWindow& window , state::Player& player) {
        std::vector<state::Card> collectedCards = player.getCollectCard(); // Get the cards on the board

        for (size_t i = 0; i < collectedCards.size(); ++i) {
            state::Card card = collectedCards[i];

            // Create a rectangle for the card
            sf::RectangleShape cardShape(sf::Vector2f(cardWidth, cardHeight));
            cardShape.setPosition(sf::Vector2f(50 + i * (cardWidth + 10), 50));  // Position on the board

            // Set the card color based on the type
            switch (card.getTypeCard()) {
            case state::TypeCard::coeur: cardShape.setFillColor(sf::Color::Red); break;
            case state::TypeCard::carreau: cardShape.setFillColor(sf::Color::Yellow); break;
            case state::TypeCard::pique: cardShape.setFillColor(sf::Color::Green); break;
            case state::TypeCard::treffle: cardShape.setFillColor(sf::Color::Blue); break;
            }

            // Add a darker border if the card is selected
            if (std::find(selectedBoardCards.begin(), selectedBoardCards.end(), i) != selectedBoardCards.end()) {
                cardShape.setOutlineColor(sf::Color::Black);  // Black border
                cardShape.setOutlineThickness(5);  // Border thickness (thicker, hence "bold")
            } else {
                cardShape.setOutlineColor(sf::Color::Transparent);  // No border if not selected
                cardShape.setOutlineThickness(1);  // Normal border size
            }

            window.draw(cardShape);  // Draw the card on the board
        }
    }

    // Add a card to the game board and draw it graphically
    void SceneData::addCardToBoard( state::Card& card) {
        // Add the card to the list of cards on the board
        boardCards.push_back(card);

        // Create a rectangle that will graphically represent the card on the board
        sf::RectangleShape cardShape(sf::Vector2f(cardWidth, cardHeight));

        // Set the card color based on its type
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

        // Set the position of the card on the board
        // Example positioning: display the cards horizontally with an offset
        float xPos = 50 + (boardCards.size() - 1) * (cardWidth + 10);
        float yPos = 50;  // Set the fixed Y position for the cards

        cardShape.setPosition(sf::Vector2f(xPos, yPos)); // Position the card

        // Add the graphical shape of the card to a list of cards on the board for drawing
        boardCardShapes.push_back(cardShape);
    }

    // Add a card to the player's hand, both logically and graphically
    void SceneData::addCardToHand(state::Card& card) {
        // Create the graphical shape for the card (rectangle representing the card)
        sf::RectangleShape cardShape(sf::Vector2f(cardWidth, cardHeight));

        // Position the card graphically in the player's hand
        float xPosition = 50 + handCardShapes.size() * (cardWidth + 10); // Horizontal position, spacing between cards
        float yPosition = boardHeight - cardHeight - 20;  // Fixed vertical position just above the bottom of the board
        cardShape.setPosition(sf::Vector2f(xPosition, yPosition));

        // Set the card color based on its type
        switch (card.getTypeCard()) {
        case state::TypeCard::coeur:
            cardShape.setFillColor(sf::Color::Red);  // Heart
            break;
        case state::TypeCard::carreau:
            cardShape.setFillColor(sf::Color::Yellow);  // Diamond
            break;
        case state::TypeCard::pique:
            cardShape.setFillColor(sf::Color::Green);  // Spade
            break;
        case state::TypeCard::treffle:
            cardShape.setFillColor(sf::Color::Blue);  // Club
            break;
        }

        // Add the graphical card to the `handCardShapes` vector for display
        handCardShapes.push_back(cardShape);  // Add the graphical shape of the card to the vector
    }

    // Remove a card from the board
    void SceneData::removeCardFromBoard(state::Card& card) {
        // Find and remove the logical card in boardCards
        auto it = std::find_if(boardCards.begin(), boardCards.end(),
                               [&card]( state::Card& c) { return c.equals(card); });
        if (it != boardCards.end()) {
            // Remove the card from the logical collection
            boardCards.erase(it);
        }

        // Find and remove the graphical card in boardCardShapes
        for (size_t i = 0; i < boardCards.size(); ++i) {
            if (boardCards[i].equals(card)) {
                // The graphical card corresponds to the index of the logical card
                boardCardShapes.erase(boardCardShapes.begin() + i);  // Remove the graphical card
                break;
            }
        }
    }

    void SceneData::removeCardFromHand(state::Card& card) {
        // Find and remove the logical card and its corresponding graphical card
        auto it = std::find_if(handCardShapes.begin(), handCardShapes.end(),
                               [&card]( std::pair<sf::RectangleShape, state::Card>& p) {
                                   return p.second.equals(card);  // Compare the logical card
                               });

        if (it != handCardShapes.end()) {
            // Remove the graphical card and the logical card
            handCardShapes.erase(it);
        }
    }

    // Select a card from the player's hand based on its index
    void SceneData::selectCardFromHand(int cardIndex) {
        if (cardIndex >= 0 && cardIndex < handCardShapes.size()) {
            selectedCardIndex = cardIndex;  // Mark the index of the selected card
        } else {
            selectedCardIndex = -1;  // No card selected if the index is invalid
        }
    }

    // Select multiple cards on the game board
    void SceneData::selectCardsFromBoard(const std::vector<int>& cardIndexes) {
        selectedBoardCards.clear();  // Reset previously selected cards

        // Add the indices of the selected cards
        for (int idx : cardIndexes) {
            if (idx >= 0 && idx < boardCardShapes.size()) {
                selectedBoardCards.push_back(idx);  // Add the index of the selected card
            }
        }
    }

    void SceneData::setSelectedCardIndex(int index){ selectedCardIndex = index; }

    // Getter for the index of the selected card
    int SceneData::getSelectedCardIndex(){ return selectedCardIndex; }

}