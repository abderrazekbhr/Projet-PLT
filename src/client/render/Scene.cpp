#include "Scene.h"
#include <iostream>
#include <filesystem>
#include <unistd.h>
#define WIDTH 1080
#define HEIGHT 720
#define MARGIN 20
#define BOX_WIDTH 150
#define BOX_HEIGHT 100

namespace render
{
    Scene::Scene(state::State &state) : playerInfo("DefaultPlayerName"), actualState(state)
    {
        // sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        window.create(sf::VideoMode(WIDTH, HEIGHT), "Game Scene");
        window.setSize(sf::Vector2u(WIDTH, HEIGHT));
        currentComponent = SceneComponent::PLAYER_A;
        init();
    }

    Scene::~Scene() {}

    void Scene::init()
    {
        // Exemple d'initialisation (couleurs, styles, etc.)
        std::cout << "Initialisation de la scène avec les données nécessaires." << std::endl;
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

    void Scene::drawScene()
    {
        // Démarre la boucle de rendu
        sf::Texture texture;
        if (!texture.loadFromFile("../assets/bg.png"))
        {
            std::cout << "error in load bg texture" << std::endl;
        }
        sf::Sprite sprite(texture);

        // Get the texture and window sizes
        sf::Vector2u textureSize = texture.getSize();
        sf::Vector2u windowSize = window.getSize();

        // Scale the sprite to fit the window
        sprite.setScale(
            static_cast<float>(windowSize.x) / textureSize.x,
            static_cast<float>(windowSize.y) / textureSize.y);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                exit(0);
            }
            if (event.type == sf::Event::Resized)
            {
                // Update the view to match the new window size
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                // Recalculate sprite scaling
                float scaleX = static_cast<float>(event.size.width) / texture.getSize().x;
                float scaleY = static_cast<float>(event.size.height) / texture.getSize().y;
                sprite.setScale(scaleX, scaleY);
            }
        }
        window.clear();

        window.draw(sprite);

        // Dessine la scène en fonction de la composante actuelle
        switch (currentComponent)
        {
        // case SceneComponent::MENU:
        //     renderMenu();
        //     break;
        // case SceneComponent::OPTION:
        //     renderOptions();
        //     break;
        case SceneComponent::PLAYER_A:
        case SceneComponent::PLAYER_B:
        case SceneComponent::PLAYER_C:
        case SceneComponent::PLAYER_D:
            renderPlayerInfo(actualState.getAllPlayers());
            break;
        // case SceneComponent::SCORE_CALCULATION:
        //     renderScores();
        //     break;
        default:
            std::cout << "Composante inconnue !" << std::endl;
            break;
        }
        this->createBoard();
        // Affiche tout ce qui a été dessiné
        window.display();
    }

    //

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
                position['x'] = MARGIN;
                position['y'] = MARGIN;
                break;
            case 1: // Top-Right
                position['x'] = WIDTH - width - MARGIN;
                position['y'] = MARGIN;
                break;
            case 2: // Bottom-Left
                position['x'] = MARGIN;
                position['y'] = HEIGHT - BOX_HEIGHT - MARGIN;
                break;
            case 3: // Bottom-Right
                position['x'] = WIDTH - width - MARGIN;
                position['y'] = HEIGHT - BOX_HEIGHT - MARGIN;
                break;
            default:
                throw std::out_of_range("Player position exceeds supported number of corners.");
            }

            positions.push_back(position); // Store the calculated position
        }
        return positions; // Return all calculated positions
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
    void Scene::createBoard()
    {
        sf::Texture texture;
        sf::RectangleShape board(sf::Vector2f(WIDTH * 0.7, HEIGHT * 0.7));
        if (!texture.loadFromFile("../assets/tapis.png"))
        {
            std::cout << "error in load bg texture" << std::endl;
        }
        texture.setSmooth(true);
        board.setPosition(WIDTH * 0.15, HEIGHT * 0.15);
        board.setTexture(&texture);

        window.draw(board);
    }

    void Scene::renderPlayerInfo(std::vector<state::Player *> players)
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
            sf::Text playerName = createText(name, font, fontSize, sf::Color(50, 50, 50), allPos[i]['x'] + 2 * paddingX, allPos[i]['y'] + spacingY);
            sf::Text playerScore = createText(score, font, fontSize, sf::Color(87, 142, 126), allPos[i]['x'] + 2 * paddingX, allPos[i]['y'] + 2 * spacingY);
            sf::RectangleShape box = createInfoPlayer(
                maxWidthBox, heightBox, sf::Color(240, 240, 240, 100), allPos[i]['x'],
                allPos[i]['y']);

            window.draw(box);
            window.draw(playerName);
            window.draw(playerScore);
        }
    }

    // void Scene::renderScores()
    // {
    //     // Exemple de rendu pour le calcul des scores
    //     sf::Font font;

    //     std::string filepath = "../assets/Luckiest_Guy/LuckiestGuy-Regular.ttf";

    //     if (!font.loadFromFile(filepath))
    //     {
    //         std::cerr << "***********Erreur : Impossible de charger la police." << std::endl;
    //     }

    //     sf::Text title("Calcul des Scores", font, 50);
    //     title.setFillColor(sf::Color::Red);
    //     title.setPosition(200, 100);

    //     sf::Text scoreCalculation("Calcul en cours...", font, 30);
    //     scoreCalculation.setFillColor(sf::Color::White);
    //     scoreCalculation.setPosition(200, 200);

    //     window.draw(title);
    //     window.draw(scoreCalculation);
    // }
}

// render::Scene scene = render::Scene(engine.getState());

// // Exemple de rendu des informations sur les joueurs
// std::string filepath = "..../assets/Luckiest_Guy/LuckiestGuy-Regular.ttf";
// sf::Font font;

// if (!font.loadFromFile(filepath))
// {
//     std::cerr << "-----------Erreur : Impossible de charger la police." << std::endl;
// }

// sf::Text playerName("Joueur: " + playerInfo.getName(), font, 30);
// playerName.setFillColor(sf::Color::Yellow);
// playerName.setPosition(200, 100);

// sf::Text playerScore("Score: " + std::to_string(playerInfo.getScore()), font, 30);
// playerScore.setFillColor(sf::Color::Yellow);
// playerScore.setPosition(200, 150);
// sf::RectangleShape player = createInfoPlayer(playerInfo.getScore(), playerInfo.getName(), playerInfo.getId());
// window.draw(playerName);

// void Scene::renderMenu()
// {
//     // Exemple de rendu d’un menu principal
//     sf::Font font;
//     std::string filepath = "../assets/Luckiest_Guy/LuckiestGuy-Regular.ttf";

//     if (!font.loadFromFile(filepath))
//     {
//         std::cerr << "Erreur : Impossible de charger la police." << std::endl;
//     }

//     sf::Text title("Menu Principal", font, 50);
//     title.setFillColor(sf::Color::White);
//     title.setPosition(200, 100);

//     sf::Text option1("1. Jouer", font, 30);
//     option1.setFillColor(sf::Color::Green);
//     option1.setPosition(200, 200);

//     sf::Text option2("2. Options", font, 30);
//     option2.setFillColor(sf::Color::Green);
//     option2.setPosition(200, 250);

//     sf::Text option3("3. Quitter", font, 30);
//     option3.setFillColor(sf::Color::Green);
//     option3.setPosition(200, 300);

//     window.draw(title);
//     window.draw(option1);
//     window.draw(option2);
//     window.draw(option3);
// }

// void Scene::renderOptions()
// {
//     // Exemple de rendu de l’écran des options
//     sf::Font font;
//     std::string filepath = "..../assets/Luckiest_Guy/LuckiestGuy-Regular.ttf";

//     if (!font.loadFromFile(filepath))
//     {
//         std::cerr << ".............Erreur : Impossible de charger la police." << std::endl;
//     }

//     sf::Text title("Options", font, 50);
//     title.setFillColor(sf::Color::White);
//     title.setPosition(200, 100);

//     sf::Text soundOption("1. Activer/Desactiver le son", font, 30);
//     soundOption.setFillColor(sf::Color::Cyan);
//     soundOption.setPosition(200, 200);

//     sf::Text backOption("2. Retour au menu", font, 30);
//     backOption.setFillColor(sf::Color::Cyan);
//     backOption.setPosition(200, 250);

//     window.draw(title);
//     window.draw(soundOption);
//     window.draw(backOption);
// }