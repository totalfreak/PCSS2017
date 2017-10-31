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

GameManager gameManager(1);
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
    srand(time(NULL));

    if(!gameStarted) {
         if(!gameManager.initGame()) {
             return 0;
         } else {
             gameStarted = true;
         }
     }
/*
    gameManager.texAmanda.loadFromFile("Client/Sprites/spr_frogTemp.png");
    gameManager.fieldList.setupFields(gameManager.fieldList, 40);
    for (int i = 0; i < 6; i++) {
    gameManager.players[i] = gameManager.createPlayer("Rasmus ", gameManager.texAmanda, gameManager.texAmanda, i,
                                                      gameManager.fieldList.getHead());
    }

    for (int i = 0; i < 6; i++) {
        cout << gameManager.players[i].myID << endl;
    }
    gameManager.players[0].setPosition(0,600);

    for(field  * ptr  = gameManager.fieldList.getHead(); ptr != nullptr ; ptr = ptr->next){
        for(int i = 0 ; i < 6 ; i++){//allow players to go to the field
            *(ptr->playersOnField + i) = FIELD_EMPTY; // set all fields to -1

        }
    }
    */

    //Making window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dice game");

    //Temp background location
    Texture bgTex;
    Sprite bgSpr;
    //int counter = 0;
    //int countto = 3000;

    //Loading the background image
    if(!bgTex.loadFromFile("Client/Sprites/board.png")) {
        cout << "Error loading BG texture";
    }
    bgSpr.setTexture(bgTex);


    // run the program as long as the window is open
    while (window.isOpen())
    {

       /* if(++counter > countto){
            for (int i = 0; i < 6; i++) {
                gameManager.players[i].moveTo(gameManager.players[i].tile->next,gameManager.players[i].myID);

            }
            for(field  * ptr  = gameManager.fieldList.getHead(); ptr != nullptr ; ptr = ptr->next){
                for(int i = 0 ; i < 6 ; i++){//allow players to go to the field
                    cout << *(ptr->playersOnField + i); // set all fields to -1
                }
                cout << " " << endl; // set all fields to -1
            }
            cout << "_____________________________________________________________________________________________" << endl; // set all fields to -1
            counter = 0;
        }
        */
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
            window.draw(gameManager.drawPlayerShadow(i));
            window.draw(gameManager.drawPlayer(i));
            window.draw(gameManager.drawPlayerPic(i));
        }

        window.display();

    }

    return 0;
}





