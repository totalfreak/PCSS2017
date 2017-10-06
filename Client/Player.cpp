#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player {
    string playerName;
    int points;
    Texture playerTexture;
    Sprite playerSprite;
    Texture playerBrickTex;
    Sprite playerBrickSpr;

public:
    bool turnTaken;
    bool isPlayersTurn;
    //Bool containing whether or not a player actually contains a person playing
    //Will also be used by server
    bool hasPlayer = false;
    Vector2i position;

    Player(string name, Texture picTex, Texture brickTex){
        playerName = name;
        playerTexture = picTex;
        playerSprite.setTexture(playerTexture);
        playerBrickTex = brickTex;
        playerBrickSpr.setTexture(playerBrickTex);
        position = Vector2i(0,0);
        points = 0;
        isPlayersTurn = false;
        turnTaken = false;
        hasPlayer = true;
    }
    Player() = default;
    void setPlayersTurn(bool x)
    {
        isPlayersTurn = x;
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
        this->playerBrickSpr.setPosition(getPosition().x, getPosition().y);
        return this->playerBrickSpr;
    }


    void movePlayer(int rolled){

        cout << endl <<  "Player " <<  playerName << " just moved " << rolled << " spaces";
        //TODO Make fit into whatever model we make the doubly linked list of Fields be
        //position += rolled;
        setPosition(getPosition().x+100, getPosition().y+200);
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



