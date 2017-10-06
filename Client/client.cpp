#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Dice.cpp"

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
        Vector2f dicePos;

        dicePos.x = window.getSize().x/2;
        dicePos.y = window.getSize().y/2;


        die1.diceSprites[0].setPosition(dicePos);
        window.clear();
        window.draw(die1.diceSprites[0]);
        window.display();
    }

    return 0;
}

Texture chooseDiceTex(int* whatIsRolled) {
    //Switch case, showing the right dice texture, dependent on what was rolled

    Texture texes[2];
    switch (whatIsRolled[0]) {
        case 1:
            texes[0] = dice1;
            break;
        case 2:
            texes[0] = dice2;
            break;
        case 3:
            texes[0] = dice3;
            break;
        case 4:
            texes[0] = dice4;
            break;
        case 5:
            texes[0] = dice5;
        case 6:
            texes[0] = dice6;
    }
    switch (whatIsRolled[1]) {
        case 1:
            texes[1] = dice1;
            break;
        case 2:
            texes[1] = dice2;
            break;
        case 3:
            texes[1] = dice3;
            break;
        case 4:
            texes[1] = dice4;
            break;
        case 5:
            texes[1] = dice5;
        case 6:
            texes[1] = dice6;
    }

    return *texes;
}