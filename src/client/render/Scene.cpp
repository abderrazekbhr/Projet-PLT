#include "Scene.h"
#include <iostream>

namespace render {

    Scene::Scene(state::State&  state)
        : window(sf::VideoMode(800, 600), "Game Scene"),
          playerInfo("DefaultPlayerName"), // Initialisation de playerInfo avec un nom par défaut
          currentComponent(SceneComponent::MENU) // Composante par défaut : MENU
    {
        // Initialisation de la scène
        init();
    }

    Scene::~Scene() {}

    void Scene::init()
    {
        // Exemple d'initialisation (couleurs, styles, etc.)
        std::cout << "Initialisation de la scène avec les données nécessaires." << std::endl;
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
            // renderPlayerInfo(actualState.getAllPlayers());
            break;
        // case SceneComponent::SCORE_CALCULATION:
        //     renderScores();
        //     break;
        default:
            std::cout << "Composante inconnue !" << std::endl;
            break;
        }
        // this->createBoard();
        // Affiche tout ce qui a été dessiné
        window.display();
    }

    //
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

    void Scene::renderPlayerInfo() {
        // Exemple de rendu des informations sur les joueurs
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Erreur : Impossible de charger la police." << std::endl;
        }

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