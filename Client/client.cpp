#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "constants.cpp"
#include "Dice.cpp"
#include "Player.cpp"


#include "Field.cpp"

using namespace std;
using namespace sf;



int main() {
    int wasRolled;
    //Making window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dice game");

    //Temp background location
    Texture bgTex;
    Sprite bgSpr;

    if(!bgTex.loadFromFile("Client/Sprites/spr_bgFrame.png")) {
        cout << "Error loading BG texture";
    }

    bgSpr.setTexture(bgTex);

    //Making the initial dice object
    Dice die1 = Dice();

    Texture playerTexture;
    if(!playerTexture.loadFromFile("Client/Sprites/player_icons/Steve.png")) {
        cout << "Error loading player texture";
    }
    Player newPlayer("Steve",playerTexture);

    //Making the field linked list
    Fields fieldList;
    for(int i = 0; i < NUMBER_OF_FIELDS; i++){
        fieldList.createField(i, "regular");
    }
    fieldList.display();

    // run the program as long as the window is open
    while (window.isOpen())
    {

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {

            //Checking for left mouse press
            if(event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Button::Left) {
                    wasRolled = die1.roll();
                    cout << " " << die1.rolled[0] << " " << die1.rolled[1] << " ";
                }
            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        Sprite dice1Spr, dice2Spr;
        die1.diceSprites[0].setPosition(100, 100);
        die1.diceSprites[1].setPosition(150, 100);
        window.clear(Color::White);
        window.draw(bgSpr);
        window.draw(die1.diceSprites[0]);
        window.draw(die1.diceSprites[1]);
        window.draw(newPlayer.display());
        window.display();

    }

    return 0;
}

