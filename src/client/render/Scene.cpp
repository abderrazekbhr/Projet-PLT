// #include "Scene.h"

// namespace render{

//     Scene::Scene():sceneElement(SceneComponent::MENU),window(sf::VideoMode(800,600),"Scene Window"),playerInfo("PlayerName"){};
//     Scene::~Scene(){};

//     void Scene::init(){

//        SceneComponent sceneComponent = SceneComponent::MENU;
//        sceneInfo.init(window, sceneComponent);

//        window.setFramerateLimit(60);
//     }

//     void Scene::drawScene(){

//         window.clear(sf::Color::Black);

//         window.draw(sceneInfo);

//         window.display();
//     }

// }