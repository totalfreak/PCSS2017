#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Dice.cpp"


using namespace std;
using namespace sf;

int main() {

    Texture dice1, dice2, dice3, dice4, dice5, dice6;

    if(!dice1.loadFromFile("Client/Sprites/spr_dice1.png") || !dice2.loadFromFile("Client/Sprites/spr_dice2.png") || !dice3.loadFromFile("Client/Sprites/spr_dice3.png") || !dice4.loadFromFile("Client/Sprites/spr_dice4.png") || !dice5.loadFromFile("Client/Sprites/spr_dice5.png") || !dice6.loadFromFile("Client/Sprites/spr_dice6.png")) {
        cout << "Error loading sprites";
    }

    //
    Sprite dice;

    //Making window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dice game");

    float circDiam = 100.f;
    CircleShape circle(circDiam);
    circle.setFillColor(Color::Cyan);

    //Making the initial dice object
    Dice die1;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {

            if(Mouse::isButtonPressed(Mouse::Button::Left)) {
                /*
                //Switch case, showing the right dice texture, dependent on what was rolled
                switch (die1.roll()) {
                    case 1:
                        dice.setTexture(dice1);
                        break;
                    case 2:
                        dice.setTexture(dice2);
                        break;
                    case 3:
                        dice.setTexture(dice3);
                        break;
                    case 4:
                        dice.setTexture(dice4);
                        break;
                    case 5:
                        dice.setTexture(dice5);
                    case 6:
                        dice.setTexture(dice6);
                }
                 */

            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                cout << die1.roll();
                window.close();
            }
        }
        Vector2f dicePos;

        dicePos.x = window.getSize().x/2;
        dicePos.y = window.getSize().y/2;


        dice.setPosition(dicePos);
        window.clear();
        window.draw(dice);
        window.display();
    }

    return 0;
}