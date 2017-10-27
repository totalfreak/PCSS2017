//inet_addr
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameManager.cpp"


using namespace std;
using namespace sf;

GameManager gameManager;
bool gameStarted = false;
bool lobbyMade = false;

void error(const char *msg) {
    perror(msg);
    exit(0);
}


void setDicePos() {
    gameManager.die.diceSprites[0].setPosition(100, 100);
    gameManager.die.diceSprites[1].setPosition(150, 100);
}

int main() {
    //Seeding random function
    srand (time(NULL));

    if(!gameStarted) {
         if(!gameManager.initGame()) {
             return 0;
         } else {
             gameStarted = true;
         }
     }

    //Making window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dice game");

    //Temp background location
    Texture bgTex;
    Sprite bgSpr;

    //Loading the background image
    if(!bgTex.loadFromFile("Client/Sprites/spr_bgFrame.jpg")) {
        cout << "Error loading BG texture";
    }
    bgSpr.setTexture(bgTex);


    // run the program as long as the window is open
    while (window.isOpen())
    {

        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            //Checking for left mouse press
            if(event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Button::Left) {
                    gameManager.roll();
                }
            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        for(int i = 0 ; i < 6 ; i++) {
            gameManager.players[i].physics();
        }

        Sprite dice1Spr, dice2Spr;

        window.clear(Color::Black);
        window.draw(bgSpr);

        gameManager.fieldList.display(window, gameManager.fieldList);

        //Drawing the dices
        setDicePos();
        window.draw(gameManager.die.diceSprites[0]);
        window.draw(gameManager.die.diceSprites[1]);
        for (int i = 0; i < 6; i++) {
            window.draw(gameManager.drawPlayer(i));
        }

        window.display();

    }

    return 0;
}





