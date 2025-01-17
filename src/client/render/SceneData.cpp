#include "SceneData.h"
#include "state.h"
#include <algorithm> // for std::find
#include <iostream>
#include <map>
#include "CardShape.h" // Include the header file where CardShape is defined
#include "GameParameters.h"
using namespace render;
using namespace std;

// Initialize the board with empty places (4 rows, 10 columns)
std::vector<std::vector<bool>> emptyPlaces(4, std::vector<bool>(10, false));

const map<int, string> cardNumber = {
    {1, "01"},
    {2, "02"},
    {3, "03"},
    {4, "04"},
    {5, "05"},
    {6, "06"},
    {7, "07"},
    {8, "08"},
    {9, "09"},
    {10, "10"}};

const map<int, string> cardType = {
    {1, "treffle"},
    {2, "carreau"},
    {3, "pique"},
    {4, "coeur"}};

// Find an empty position on the board
std::pair<int, int> getEmptyPlace()
{
    for (int j = 0; j < 4; j++) // Iterate through rows (4 rows)
    {
        for (int i = 0; i < 10; i++) // Iterate through columns (10 columns)
        {
            if (!emptyPlaces[j][i]) // If the position is not occupied
            {
                emptyPlaces[j][i] = true;    // Mark it as occupied
                return std::make_pair(j, i); // Return the position
            }
        }
    }

    // Return an invalid position if no space is available
    return std::make_pair(-1, -1);
}

std::vector<std::map<char, double>> generatePlayersPositions(int nbPlayer, double width, double height)
{
    std::vector<std::map<char, double>> positions;

    for (int i = 0; i < nbPlayer; i++)
    {
        std::map<char, double> position;

        // Determine corner placement (0: Top-Left, 1: Top-Right, 2: Bottom-Left, 3: Bottom-Right)
        switch (i)
        {
        case 0: // Top-Left
            position['x'] = GameParameters::MARGIN;
            position['y'] = GameParameters::MARGIN;
            break;
        case 1: // Top-Right
            position['x'] = GameParameters::WIDTH - width - GameParameters::MARGIN;
            position['y'] = GameParameters::MARGIN;
            break;
        case 2: // Bottom-Left
            position['x'] = GameParameters::MARGIN;
            position['y'] = GameParameters::HEIGHT - GameParameters::BOX_HEIGHT - GameParameters::MARGIN;
            break;
        case 3: // Bottom-Right
            position['x'] = GameParameters::WIDTH - width - GameParameters::MARGIN;
            position['y'] = GameParameters::HEIGHT - GameParameters::BOX_HEIGHT - GameParameters::MARGIN;
            break;
        default:
            throw std::out_of_range("Player position exceeds supported number of corners.");
        }

        positions.push_back(position); // Store the calculated position
    }
    return positions; // Return all calculated positions
}

sf::Font createFont(std::string filepath)
{
    sf::Font font;
    if (!font.loadFromFile(filepath))
    {
        std::cerr << "Erreur : Impossible de charger la police." << std::endl;
    }
    return font;
}

// Create a text object
sf::Text createText(const std::string &text, const sf::Font &font, int size, sf::Color color, int x, int y)
{
    sf::Text title;
    title.setFont(font);
    title.setString(text);
    title.setCharacterSize(size);
    title.setFillColor(color);
    title.setPosition(x, y);
    return title;
}

// Create a rectangle for player info
sf::RectangleShape createInfoPlayer(int width, int height, sf::Color bg, int posX, int posY)
{
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setPosition(posX, posY);
    rectangle.setFillColor(bg);
    rectangle.setOutlineColor(sf::Color(61, 61, 61));

    return rectangle;
}

int maxSizeName(std::vector<state::Player *> players)
{
    int size = players[0]->getName().size();
    for (state::Player *p : players)
    {
        int len = p->getName().size();
        if (size < len)
        {
            size = len;
        }
    }
    return size;
}

// Constructor
SceneData::SceneData()
{
    bordWidth = 800;
    boardHeight = 700;
    cardWidth = 80;
}

// Destructor
SceneData::~SceneData() = default;

// Draw the cards on the hand of the player
// Draw the cards on the player's board
void SceneData::drawCardsOnBoard(sf::RenderWindow &window, state::GameBoard &board)
{
    // Retrieve the cards on the board
    std::vector<state::Card> cards = board.getCardBoard();
    int size = cards.size();

    // Define starting positions and margins
    const float START_X = GameParameters::WIDTH * 0.12f;
    const float START_Y = GameParameters::HEIGHT * 0.15f;
    const float C_MARGIN_X = 2.0f;
    const float C_MARGIN_Y = 4.0f;
    emptyPlaces = std::vector<std::vector<bool>>(4, std::vector<bool>(10, false));
    for (int i = 0; i < size; ++i)
    {
        // Find an empty place on the board
        std::pair<int, int> place = getEmptyPlace();
        if (place.first == -1 && place.second == -1)
        {
            std::cout << "No more space for cards" << std::endl;
            return;
        }

        // Retrieve the current card
        state::Card card = cards[i];

        // Prepare the file path for the card image
        std::string cardPath = "../assets/cards/" + cardType.at(card.getTypeCard()) + "_" + cardNumber.at(card.getNumberCard()) + ".png";

        // Calculate the card's position
        float posX = place.second * (GameParameters::C_WIDTH + 2 * C_MARGIN_X) + START_X;
        float posY = place.first * (GameParameters::C_HEIGHT + 2 * C_MARGIN_Y) + START_Y;

        // Create the graphical object for the card
        CardShape cardShape(
            posX,                   // X position
            posY,                   // Y position
            70,                     // Width of the card
            120,                    // Height of the card
            cardPath, true, &card); // Visibility and card reference

        // Draw the card on the window
        window.draw(cardShape);
    }
}

// Draw the cards on the hand of the player
void SceneData::drawCardsOnHand(sf::RenderWindow &window, state::Player &player)
{
    std::vector<state::Card> heldCards = player.getHoldCard();
    int size = heldCards.size();

    for (int i = 0; i < size; ++i)
    {
        state::Card card = heldCards[i];

        // Prepare the path to the card image
        std::string cardPath = "../assets/cards/" + cardType.at(card.getTypeCard()) + "_" + cardNumber.at(card.getNumberCard()) + ".png";

        // Create CardShape object
        CardShape cardShape(
            GameParameters::WIDTH / 1.8 + (i - 2) * (GameParameters::C_WIDTH + 10), // Position en x
            GameParameters::HEIGHT - GameParameters::C_HEIGHT,                      // Position en y
            GameParameters::C_WIDTH,                                                // Largeur
            GameParameters::C_HEIGHT,                                               // Hauteur
            cardPath, true, &card);                                                 // Visibilité
        window.draw(cardShape);
    }
}

void SceneData::addCardToBoard(state::Card &card)
{
    boardCards.push_back(card);
}

void SceneData::addCardToHand(state::Card &card)
{
    boardCards.push_back(card);
}

void SceneData::removeCardFromBoard(state::Card &card)
{
    auto it = std::find_if(boardCards.begin(), boardCards.end(), [&card](state::Card &c)
                           { return c.equals(card); });
    if (it != boardCards.end())
    {
        boardCards.erase(it);
    }
}

void SceneData::removeCardFromHand(state::Card &card)
{
    auto it = std::find_if(boardCards.begin(), boardCards.end(), [&card](state::Card &c)
                           { return c.equals(card); });
    if (it != boardCards.end())
    {
        boardCards.erase(it);
    }
}

// Sélectionner une carte de la main du joueur en fonction de son index
void SceneData::selectCardFromHand(int cardIndex)
{
    int size = handCardShapes.size();
    if (cardIndex >= 0 && cardIndex < size)
    {
        selectedCardIndex = cardIndex; // Marquer l'index de la carte sélectionnée
    }
    else
    {
        selectedCardIndex = -1; // Aucune carte sélectionnée si l'index est invalide
    }
}

// Sélectionner plusieurs cartes sur le plateau de jeu
void SceneData::selectCardsFromBoard(std::vector<int> &cardIndexes)
{
    selectedBoardCards.clear(); // Réinitialiser les cartes sélectionnées précédemment

    // Ajouter les indices des cartes sélectionnées
    for (int idx : cardIndexes)
    {
        int size = boardCardShapes.size();
        if (idx >= 0 && idx < size)
        {
            selectedBoardCards.push_back(idx); // Ajouter l'index de la carte sélectionnée
        }
    }
}

void SceneData::setSelectedCardIndex(int index)
{
    selectedCardIndex = index;
}

int SceneData::getSelectedCardIndex()
{
    return selectedCardIndex;
}

sf::RectangleShape SceneData::drawCard(std::string img, float width, float height, float posX, float posY)
{
    std::string PATH = "../assets/card/";
    sf::RectangleShape card;
    sf::Texture texture;

    if (!texture.loadFromFile(PATH + img))
    {
        std::cout << "error can't load card texture " << img << std::endl;
    }
    card.setTexture(&texture);
    card.setSize({width,
                  height});
    card.setPosition({posX, posY});

    return card;
}

void SceneData::createBoard()
{
    sf::RectangleShape gameBoard(sf::Vector2f(GameParameters::WIDTH * 0.8, GameParameters::HEIGHT * 0.7));
    if (!boardTexture.loadFromFile("../assets/tapis.png"))
    {
        std::cout << "error in load bg texture" << std::endl;
        return;
    }
    gameBoard.setPosition(GameParameters::WIDTH * 0.10, GameParameters::HEIGHT * 0.15);
    gameBoard.setTexture(&boardTexture);

    this->board = gameBoard;
}

void SceneData::renderPlayerInfo(sf::RenderWindow &window, std::vector<state::Player *> players, int indexCurrentPlayer)
{
    std::string filepath = "../assets/Luckiest_Guy/LuckiestGuy-Regular.ttf";
    sf::Font font = createFont(filepath);
    int paddingX = 20;
    int fontSize = 18;
    int spacingY = 20;
    const std::string START_NAME = "Player:";
    const std::string START_SCORE = "Score:";

    double maxWidthBox = maxSizeName(players);
    maxWidthBox += START_NAME.size();
    maxWidthBox *= fontSize / 1.5;
    maxWidthBox += paddingX * 2;
    double heightBox = 2 * (fontSize + spacingY);
    std::vector<std::map<char, double>> allPos = generatePlayersPositions(players.size(), maxWidthBox, heightBox);
    for (size_t i = 0; i < players.size(); i++)
    {

        std::string name = START_NAME + players[i]->getName();
        std::string score = START_SCORE + std::to_string(players[i]->getScore());
        sf::Text playerName = createText(name, font, fontSize, sf::Color(50, 50, 50, 255), allPos[i]['x'] + 2 * paddingX, allPos[i]['y'] + spacingY);
        sf::Text playerScore = createText(score, font, fontSize, sf::Color(87, 142, 126, 255), allPos[i]['x'] + 2 * paddingX, allPos[i]['y'] + 2 * spacingY);
        sf::RectangleShape box = createInfoPlayer(
            maxWidthBox, heightBox, sf::Color(240, 240, 240, 200), allPos[i]['x'],
            allPos[i]['y']);
        playersName.push_back(playerName);
        playersScore.push_back(playerScore);
        if (i == indexCurrentPlayer)
        {
            box.setOutlineThickness(4);
            box.setOutlineColor(sf::Color(61, 170, 51, 150));
        }
        window.draw(box);
        window.draw(playerName);
        window.draw(playerScore);
    }
}

void render::SceneData::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Exemple : Dessiner le plateau et les cartes graphiques
    target.draw(board, states); // Dessine le plateau

    // Dessiner toutes les cartes sur le plateau
    for (const auto &cardShape : boardCardShapes)
    {
        target.draw(cardShape, states);
    }

    // Dessiner toutes les cartes dans la main
    for (const auto &handShape : handCardShapes)
    {
        std::cout << "draw player shape" << std::endl;
        target.draw(handShape, states);
    }

    // Dessiner le texte associé (si besoin)
    for (sf::Text txt : playersName)
    {
        std::cout << "draw player name" << std::endl;
        target.draw(txt, states);
    }
    for (sf::Text txt : playersScore)
    {
        std::cout << "draw player score" << std::endl;

        target.draw(txt, states);
    }
}
