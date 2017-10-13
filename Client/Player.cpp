#include <iostream>
#include <SFML/Graphics.hpp>

#include <cmath>
#include "Fields.h"

using namespace std;
using namespace sf;

class Player {
    string playerName;
    int points;
    Texture playerTexture;
    Sprite playerSprite;
    float DEFAULTSPEED = 20;


public:
    Texture playerBrickTex;
    Sprite playerBrickSpr;
    bool turnTaken;
    bool isPlayersTurn;
    //Bool containing whether or not a player actually contains a person playing
    //Will also be used by server
    bool hasPlayer = false;
    Vector2f position;
    float speed;
    int myID;
    field tile; // the current tile this player is heading towards

    Player(string name, Texture picTex, Texture brickTex, int ID) {
        playerName = name;
        playerTexture = picTex;
        playerSprite.setTexture(playerTexture);
        playerBrickTex = brickTex;
        playerBrickSpr.setTexture(playerBrickTex);
        position = Vector2f(540,540);
        points = 0;
        isPlayersTurn = false;
        turnTaken = false;
        hasPlayer = true;
        speed = DEFAULTSPEED;
        myID = ID;
    }
    Player() = default;
    void setPlayersTurn() {
        isPlayersTurn = true;
        cout << endl << this->playerName << "'s turn began" << endl;
    }

    Vector2f getPosition(){
        return position;
    }
    void setPosition(Vector2f pos) {
        this->position = pos;
    }
    void setPosition(int tempX, int tempY) {
        this->position = Vector2f(tempX, tempY);
    }



    void physics(){
        if(&tile == nullptr){return;}
        int nrOnField;
        int myNr;
        int playerID;
        for(int i = 0; i < 6 ; i ++){
            if(playerID = tile.playersOnField + i != nullptr){
                nrOnField++;
                if(playerID == myID){myNr = nrOnField;}
            }
        }
        nrOnField++; // we increment to avoid having people at the ends of the tile
        Vector2f goal;
        if(nrOnField < 3){
            goal = Vector2f(tile.position.x + tile.size.x/2 , tile.position.y + tile.position.y  * 0.1 + 0.8 * (myNr/nrOnField) * tile.size.y );
        }else{

        }

        float dist;
        if(dist = distance(goal, getPosition()) < speed){
            if(dist < 1){return;}
            setPosition(goal);
        }
        Vector2f moveDirection = Vector2f(goal - getPosition());
        normalize(moveDirection);
        moveDirection *= speed;
        setPosition( getPosition() + moveDirection);
    }

    float distance(Vector2f one, Vector2f two){
        float dist = pow(one.x - two.x, 2) + pow(one.y - two.y , 2); //phythaoran theorem
        return sqrt(dist); // now we have the length of the hypotenus
    }

    Vector2f normalize(Vector2f in){
        float length = pow(in.x,2) + pow(in.y,2); //phythaoran theorem
        length = sqrt(length); // now we have the length of the hypotenuse
        in *= 1/length;
        return in;
    }

    Sprite display(){
        playerBrickSpr.setTexture(playerBrickTex);
        this->playerBrickSpr.setPosition(getPosition().x, getPosition().y);
        return this->playerBrickSpr;
    }


    void movePlayer(int rolled){

        cout << endl <<  "Player " <<  playerName << " just moved " << rolled << " spaces";
        //TODO Make fit into whatever model we make the doubly linked list of Fields be

        field * dest = &tile;
        //iterate throught he field
        for(int i = 0 ; i < rolled ; i++){

            if(dest->next != nullptr) {
                dest = dest->next;
            }
        }
        moveTo(dest);
    }

    void moveTo(field * dest){
        if(dest != nullptr){
            //delete us on the field we are on
            for(int i = 0 ; i < 6 ; i++) {
                if ( *(tile.playersOnField + i) == myID) {
                    *(tile.playersOnField + i) = -1; // we use -1 to denote that no players are on the this index of the array
                }
            }
            // then add us at the destination
            tile = *dest;
            for(int i = 0 ; i < 6 ; i++) {
                if ( *(tile.playersOnField + i) == -1) {
                    *(tile.playersOnField + i) = myID;
                }
            }

        }
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



