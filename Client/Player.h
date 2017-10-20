//
// Created by rasmus on 10/13/17.
//

#ifndef PCSS2017_PLAYER_H
#define PCSS2017_PLAYER_H
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include <cmath>
#include "Fields.h"
#include <chrono>


using namespace std;
using namespace sf;
using namespace std::chrono;

class Player {

    string playerName;
    int points;
    Texture playerTexture;
    Sprite playerSprite;


    //physics stuff
    float DEFAULTSPEED = 100;
    high_resolution_clock::time_point LastMove = high_resolution_clock::now();
    high_resolution_clock::time_point tempTime;
    float movescaleAdjust = 100; // prevents the sprite from being to big during move



public:
    Texture playerBrickTex;
    Sprite playerBrickSpr;
    bool turnTaken;
    bool isPlayersTurn;
    //Bool containing whether or not a player actually contains a person playing
    //Will also be used by server
    bool hasPlayer = false;
    Vector2f position;

    //physics
    float speed;//
    float distanceFactor = 1.5;
    float currentSpeed;


    int myID;
    field * tile; // the current tile this player is heading towards


    //constructors
    Player() = default;


    // gamestate actions
    void setPlayersTurn();
    void endTurn();
    void chooseAction();

    Vector2f getPosition();
    void setPosition(Vector2f pos);
    void setPosition(int tempX, int tempY);

    //displays
    Sprite display();



    //game things
    void physics();     //move player
    float distance(Vector2f one, Vector2f two); // computes distance
    void normalize(Vector2f * in);    //normalizes a vector
    void movePlayer(int rolled);    //tell a player to move to a place
    void moveTo(field * dest);      //deletes spot at current tile and gives them a spot at the destinaiton
    double getMoveTime();

    Player(string name, Texture picTex, Texture brickTex, int ID, field *pos);
};

#endif //PCSS2017_PLAYER_H
