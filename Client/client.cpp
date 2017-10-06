#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>

using namespace std;
using namespace sf;

int main() {


    Texture dice1, dice2, dice3, dice4, dice5, dice6;

    if(!dice1.loadFromFile("Client/Sprites/spr_dice1.png") || !dice2.loadFromFile("Client/Sprites/spr_dice2.png") || !dice3.loadFromFile("Client/Sprites/spr_dice3.png") || !dice4.loadFromFile("Client/Sprites/spr_dice4.png") || !dice5.loadFromFile("Client/Sprites/spr_dice5.png") || !dice6.loadFromFile("Client/Sprites/spr_dice6.png")) {
        cout << "Error loading sprites";
    }
    Sprite dice;


    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    float circDiam = 100.f;
    CircleShape circle(circDiam);
    circle.setFillColor(Color::Cyan);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        Vector2f mousePos;

        dice.setTexture(dice1);

        mousePos.x = (int) Mouse::getPosition(window).x-16;
        mousePos.y = (int) Mouse::getPosition(window).y-16;

        dice.setPosition(mousePos);
        window.clear();
        window.draw(dice);
        window.display();
    }

    return 0;
}