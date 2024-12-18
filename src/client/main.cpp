#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>

void testSFML()
{
    sf::Texture texture;
}
// end of test SFML

#include "../shared/state.h"
using namespace std;

int main()
{
    int x = 1080;
    int y = 720;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello Window");
    sf::Texture texture;
    std::string path = "ressources.png";
    if (!texture.loadFromFile(path))
    {
        std::cout << "Could not load enemy texture" << std::endl;
        return 0;
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        sf::Sprite image;
        image.setTexture(texture);
        image.setPosition(sf::Vector2f(x, y));
        image.scale(sf::Vector2f(1, 1.5));
        window.clear();
        window.draw(image);
        window.display();
    }

    return 0;
}

// int main(int argc, char *argv[])
// {
//     cout << "Bonjour, c'est jeux du carte CHKOBA!" << endl;

//     return 0;
// }
