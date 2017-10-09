#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "constants.cpp"
#include "GameManager.cpp"


#include "Field.cpp"

using namespace std;
using namespace sf;


GameManager gameManager;
bool gameStarted = false;

void initGame() {
    //Seeding random function
    srand (time(NULL));
    //Making new game manager with desired amount of players
    cout << "How many players are playing at this time?" << endl;
    int amountOfPlayers;
    cin >> amountOfPlayers;
    if(amountOfPlayers <= 6 && amountOfPlayers > 0) {
        gameManager = GameManager(amountOfPlayers);
        gameManager.currentPlayer = 1;
        gameManager.players[gameManager.currentPlayer - 1].setPlayersTurn();
        gameStarted = true;
    } else {
        cout << "Try one more time" << endl;
        initGame();
    }
}


void setDicePos() {
    gameManager.die.diceSprites[0].setPosition(100, 100);
    gameManager.die.diceSprites[1].setPosition(150, 100);
}

int main() {

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
        Event event;
        while (window.pollEvent(event))
        {
            //Checking for left mouse press
            if(event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Button::Left) {
                    gameManager.takeTurn();
                }
            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        if(!gameStarted) {
            initGame();
        }

        Sprite dice1Spr, dice2Spr;

        window.clear(Color::Black);
        window.draw(bgSpr);
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



