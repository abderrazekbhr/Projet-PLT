// Generated by dia2code
#ifndef RENDER__SCENEDATA__H
#define RENDER__SCENEDATA__H

#include <vector>
#include <SFML/Graphics.hpp>

namespace sf {
  class RenderWindow;
  class Drawable;
  class Transformable;
};
namespace render {
  class CardPosition;
}

#include "CardPosition.h"

namespace render {

  /// class SceneData - 
  class SceneData : public sf::Drawable, public sf::Transformable {
    // Associations
    // Attributes
  public:
    std::vector<sf::Text> text;
    Sfml::Font font;
    sf::RectangleShape board;
    static CardPosition cardPos;
  private:
    double bordWidth;
    double boardHeight;
    std::vector<sf::RectangleShape> cards;
    double cardWidth;
    double cardHeight;
    // Operations
  public:
    SceneData ();
    ~SceneData ();
    void init (sf::RenderWindow& window, SceneComponent& id);
    void update (state::Player& playerInfo, int turn);
    void drawSceneData (sf::RenderWindow& window);
    void const draw (sf:: RenderTarget& target, sf::RenderStates states);
    void drawCardsOnHand (sf::RenderWindow& window);
    void drawCardsOnBoard (sf::RenderWindow& window);
    void addCardToBoard (std::vector<Card> cards);
    void addCardToHand (std::vector<Card> cards);
    void removeCardFromBoard (Card card);
    void removeCardFromHand (Card card);
    Card selectCardFromHand (int cardIndex);
    std::vector<Card> selectCardFromBoard (std::vector<int> cardIndexs);
    // Setters and Getters
  };

};

#endif
