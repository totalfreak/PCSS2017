#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player {
    string playerName;
    int position; //between 0 and 39
    int points;
    Texture playerTexture;
    Sprite playerSprite;

public:

    bool turnTaken;
    bool isPlayersTurn;
    //Bool containing whether or not a player actually contains a person playing
    //Will also be used by server
    bool hasPlayer;

    Player(string name, Texture tex){
        playerName = name;
        playerTexture = tex;
        playerSprite.setTexture(playerTexture);
        position = 0;
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
    int getPosition(){
        return position;
    }
    Sprite display(){
        playerSprite.setPosition(600, 0);
        return playerSprite;
    }


    void movePlayer(int rolled){

        cout << endl <<  "Player " <<  playerName << " just moved " << rolled << " spaces";
        //TODO Make fit into whatever model we make the doubly linked list of Fields be
        //position += rolled;
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



