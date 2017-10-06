#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Dice.cpp"
#include "Player.cpp"


#include "Field.cpp"

using namespace std;
using namespace sf;


int main() {



    //Making window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dice game");

    float circDiam = 100.f;
    CircleShape circle(circDiam);
    circle.setFillColor(Color::Cyan);

    //Making the initial dice object
    Dice die1;
    Player newPlayer("Steve");


    // run the program as long as the window is open
    while (window.isOpen())
    {

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {

            if(Mouse::isButtonPressed(Mouse::Button::Left)) {
                die1.chooseDiceTex(die1.roll());
            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                cout << die1.roll();
                window.close();
            }
        }

        //Setting position of dices
        Vector2f dicePos1, dicePos2;
        dicePos1.x = window.getSize().x/2;
        dicePos1.y = window.getSize().y/2;
        dicePos2.x = 100;
        dicePos2.y = window.getSize().y/2;


        die1.diceSprites[0].setPosition(dicePos1);
        die1.diceSprites[1].setPosition(dicePos2);
        window.clear();
        window.draw(die1.diceSprites[0]);
        window.draw(die1.diceSprites[1]);
        window.display();
    }

    return 0;
}

