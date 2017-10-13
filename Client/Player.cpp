#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>

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
    Vector2f goal; // position that this player is moving towards
    float speed;
    int playerID;

    Player(string name, Texture picTex, Texture brickTex, int ID) {
        playerName = name;
        playerTexture = picTex;
        playerSprite.setTexture(playerTexture);
        playerBrickTex = brickTex;
        playerBrickSpr.setTexture(playerBrickTex);
        position = Vector2f(540,540);
        goal = position;
        points = 0;
        isPlayersTurn = false;
        turnTaken = false;
        hasPlayer = true;
        speed = DEFAULTSPEED;
        playerID = ID;
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

    void setGoal(Vector2f goal){// used to make the player move towards the position
        position = goal;
    }
    Vector2f getGoal(){ // return the location the player is moving towards
        return goal;
    }

    void physics(){

        float dist;
        if(dist = distance(getGoal() , getPosition()) < speed){
            if(dist < 1){return;}
            setPosition(goal);
        }
        Vector2f moveDirection = Vector2f(getGoal() - getPosition());
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
        //position += rolled;
        Vector2f moveDistance = Vector2f(0,100);
        setGoal(getPosition() + moveDistance);
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



