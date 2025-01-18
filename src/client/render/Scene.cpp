#include "Scene.h"
#include <iostream>
#include <filesystem>
#include <unistd.h>

#include "GameParameters.h"
namespace render
{
    Scene::Scene(state::State &state) : playerInfo("DefaultPlayerName"), actualState(state)
    {
        // sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        window.create(sf::VideoMode(GameParameters::WIDTH, GameParameters::HEIGHT), "CHKOBA");

        currentComponent = SceneComponent::PLAYER_A;
        init();
    }

    Scene::~Scene() {}

    void Scene::init()
    {
        // Exemple d'initialisation (couleurs, styles, etc.)
        std::cout << "Initialisation de la scène avec les données nécessaires." << std::endl;
    }

    void Scene::drawScene(int cindex, std::vector<int> indexs)
    {

        window.clear();
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
        window.clear();
        window.draw(sprite);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                exit(0);
            }
        }

        // create board and display it
        sceneInfo.createBoard();
        window.draw(sceneInfo.board);

        std::vector<state::Player *> allPlayer = actualState.getAllPlayers();
        state::GameBoard *board = actualState.getBoard();
        sceneInfo.renderPlayerInfo(window, allPlayer, actualState.turn);

        // display actual player cards
        int index = actualState.turn;
        state::Player *player = actualState.getAllPlayers()[index];
        sceneInfo.drawCardsOnHand(window, *player, cindex);

        // display board cards
        sceneInfo.drawCardsOnBoard(window, *board, indexs);

        // display window
        window.display();
    }
}
