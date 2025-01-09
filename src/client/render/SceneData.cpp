#include "SceneData.h"
#include "state.h"
#include <algorithm> // for std::find

namespace render {

    CardPosition SceneData::cardPos;

    SceneData::SceneData()
        : selectedCardIndex(-1),bordWidth(800.0), boardHeight(600.0), cardWidth(80.0), cardHeight(120.0) {}

    SceneData::~SceneData() {}

    void SceneData::init(sf::RenderWindow &window, SceneComponent &id) {
        if (!font.loadFromFile("arial.ttf")) {
            throw std::runtime_error("Failed to load font 'arial.ttf'");
        }

        board.setSize(sf::Vector2f(bordWidth, boardHeight));
        board.setFillColor(sf::Color(200, 200, 255));
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

    void SceneData::draw(sf::RenderTarget &target, sf::RenderStates states) {
        target.draw(board, states);

        for (auto &card : boardCardShapes) {
            target.draw(card, states);
        }

        for (auto &card : boardCardShapes) {
            target.draw(card, states);
        }

        for (auto &t : text) {
            target.draw(t, states);
        }
    }

    void SceneData::drawCardsOnHand(sf::RenderWindow &window, state::Player &player) {
        auto  heldCards = player.getHoldCard();
        for (size_t i = 0; i < heldCards.size(); ++i) {
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

    void SceneData::drawCardsOnBoard(sf::RenderWindow &window, state::Player &player) {
        auto collectedCards = player.getCollectCard();
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

    void SceneData::selectCardFromHand(int cardIndex) {
        selectedCardIndex = (cardIndex >= 0 && cardIndex < static_cast<int>(boardCards.size())) ? cardIndex : -1;
    }

    void SceneData::selectCardsFromBoard(std::vector<int> &cardIndexes) {
        selectedBoardCards = cardIndexes;
    }

    void SceneData::setSelectedCardIndex(int index) {
        selectedCardIndex = index;
    }

    int SceneData::getSelectedCardIndex() {
        return selectedCardIndex;
    }

} // namespace render
