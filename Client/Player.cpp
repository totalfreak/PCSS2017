#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player {
    string playerName;
    int points;
    Texture playerTexture;
    Sprite playerSprite;


public:
    Texture playerBrickTex;
    Sprite playerBrickSpr;
    bool turnTaken;
    bool isPlayersTurn;
    //Bool containing whether or not a player actually contains a person playing
    //Will also be used by server
    bool hasPlayer = false;
    Vector2i position;

    Player(string name, Texture picTex, Texture brickTex) {
        playerName = name;
        playerTexture = picTex;
        playerSprite.setTexture(playerTexture);
        playerBrickTex = brickTex;
        playerBrickSpr.setTexture(playerBrickTex);
        position = Vector2i(540,540);
        points = 0;
        isPlayersTurn = false;
        turnTaken = false;
        hasPlayer = true;
    }
    Player() = default;
    void setPlayersTurn() {
        isPlayersTurn = true;
        cout << endl << this->playerName << "'s turn began" << endl;
    }
    Vector2i getPosition(){
        return position;
    }
    void setPosition(Vector2i pos) {
        this->position = pos;
    }
    void setPosition(int tempX, int tempY) {
        this->position = Vector2i(tempX, tempY);
    }
    Sprite display(){
        playerBrickSpr.setTexture(playerBrickTex);
        this->playerBrickSpr.setPosition(getPosition().x, getPosition().y);
        return this->playerBrickSpr;
    }


    void movePlayer(int rolled){

        cout << endl <<  "Player " <<  playerName << " just moved " << rolled << " spaces";
        //TODO Make fit into whatever model we make the doubly linked list of Fields be
        //position += rolled;
        setPosition(getPosition().x-rolled, getPosition().y);
    }
    void endTurn(){
        isPlayersTurn = false;
        cout << endl << this->playerName << "'s turn ended" << endl;
        //inform the server
    }
    void chooseAction(){
        if(isPlayersTurn)
        {

            //Do something related to what field you landed on here

            endTurn();
            //Inform the server
        }
    }
};



