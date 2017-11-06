//
// Created by rasmus on 10/13/17.
//

#ifndef PCSS2017_PLAYER_H
#define PCSS2017_PLAYER_H
#include <iostream>
#include <SFML/Graphics.hpp>

#include <cmath>
#include "Fields.h"
#include <chrono>


using namespace std;
using namespace sf;
using namespace std::chrono;

class Player {


    int points;
    Texture playerTexture;
    Sprite playerSprite;


    //physics stuff
    float DEFAULTSPEED = 100;
    high_resolution_clock::time_point LastMove = high_resolution_clock::now();
    high_resolution_clock::time_point tempTime;
    float movescaleAdjust = 100; //Prevent the sprite from being too big during move



public:
    string playerName;
    Texture playerBrickTex;
    Sprite playerBrickSpr;
    bool turnTaken;
    bool isPlayersTurn;
    //Bool containing whether or not a player actually contains a person playing
    //Will also be used by server
    bool hasPlayer = false;
    Vector2f position;
    int hasSelectedPic = -1;

    //Physics
    float speed;//
    float distanceFactor = 1.5;
    float currentSpeed;
    bool reachedEnd = false;

    int myID;
    field * tile; //The current tile this player is heading towards


    //constructors
    Player() = default;


    //Game state actions
    void setPlayersTurn();
    void endTurn();
    void chooseAction();
    void setPic(int num);

    Vector2f getPosition();
    void setPosition(Vector2f pos);
    void setPosition(int tempX, int tempY);

    //displays
    Sprite display();
    Sprite displayPic();
    Sprite displayShadow();


    //Game functions
    void physics();     //Move player
    float distance(Vector2f one, Vector2f two); //Computes distance
    void normalize(Vector2f * in);    //Normalizes a vector
    void movePlayer(int rolled);    //Tells a player to move to a place
    void moveTo(field *dest, int IDToLookFor);      //Deletes spot at current tile and gives them a spot at the destinaiton
    double getMoveTime();

    Player(string name, Texture picTex, Texture brickTex, int ID, field *pos);



};

#endif //PCSS2017_PLAYER_H
