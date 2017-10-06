#include "_G_config.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "client.h"
#include "Dice.cpp"

using namespace std;
using namespace sf;

int main() {
    sf::Window window(sf::VideoMode(800, 600), "My window");


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
    }

    return 0;
}