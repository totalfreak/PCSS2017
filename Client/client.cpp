#include <iostream>
#include <SFML/Graphics.hpp>
#include "Dice.cpp"
#include <SFML/Main.hpp>

using namespace std;
using namespace sf;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    float circDiam = 100.f;
    CircleShape circle(circDiam);
    circle.setFillColor(Color::Cyan);


    Dice die1;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                cout << die1.roll();
                window.close();
            }
        }
        Vector2f mousePos;

        mousePos.x = (int) Mouse::getPosition(window).x-circDiam;
        mousePos.y = (int) Mouse::getPosition(window).y-circDiam;

        circle.setPosition(mousePos);
        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}