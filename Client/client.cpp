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

    if(!bgTex.loadFromFile("Client/Sprites/spr_bgFrame.jpg")) {
        cout << "Error loading BG texture";
    }

    bgSpr.setTexture(bgTex);

    //Making the initial dice object
    Dice die1 = Dice();

    Texture textureAhmad;
    if(!textureAhmad.loadFromFile("Client/Sprites/player_icons/Ahmad.png")) {
        cout << "Error loading player texture Ahmad";
    }
    Player Ahmad("Ahmad",textureAhmad);

    Texture textureAmanda;
    if(!textureAmanda.loadFromFile("Client/Sprites/player_icons/Amanda.png")) {
        cout << "Error loading player texture Amanda";
    }
    Player Amanda("Amanda",textureAmanda);

    Texture textureKevin;
    if(!textureKevin.loadFromFile("Client/Sprites/player_icons/Kevin.png")) {
        cout << "Error loading player texture Kevin";
    }
    Player Kevin("Kevin",textureKevin);

    Texture textureCarl;
    if(!textureCarl.loadFromFile("Client/Sprites/player_icons/Carl.png")) {
        cout << "Error loading player texture Carl";
    }
    Player Carl("Carl",textureCarl);

    Texture textureSteve;
    if(!textureSteve.loadFromFile("Client/Sprites/player_icons/Steve.png")) {
        cout << "Error loading player texture Steve";
    }
    Player Steve("Steve",textureSteve);

    Player currentPlayer("Steve",textureSteve);
    srand (time(NULL));

    switch (rand()%5){
        case 1:
             currentPlayer = Steve;
            break;
        case 2:
             currentPlayer = Ahmad;
            break;
        case 3:
             currentPlayer = Amanda;
            break;
        case 4:
             currentPlayer = Carl;
            break;
        case 5:
             currentPlayer = Kevin;
            break;
    }

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
        window.clear(Color::Black);
        window.draw(bgSpr);
        window.draw(die1.diceSprites[0]);
        window.draw(die1.diceSprites[1]);
        window.draw(currentPlayer.display());
        window.display();

    }

    return 0;
}

