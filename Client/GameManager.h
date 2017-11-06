//
// Created by rasmus on 11/2/17.
//

#ifndef PCSS2017_GAMEMANAGER_H
#define PCSS2017_GAMEMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Fields.h"
#include "Player.h"
#include "Dice.h"
#include "Server/Server.h"
#include "Client.h"
#include<sys/socket.h>    //socket
#include<arpa/inet.h>
#include "MainMenu.h"
#include "Lobby.h"

class Lobby;
class Client;

struct cueNode{
    char msg[1024];
    cueNode * next;
};

class GameManager {

public:

    bool locked;
    thread serverThread, clientThread;

    int sock;

    struct sockaddr_in server;


    //cue of orders from network
    cueNode * cueHead;
    cueNode * cueTail;

    //
    Server server1 = Server(6);
    Client * client1;
    MainMenu menu;
    Lobby * lobby;

    Dice die = Dice();
    //Making the player objects and storing them in the player array
    Player player1, player2, player3, player4, player5, player6;
    Player players[6] = {player1, player2, player3, player4, player5, player6};

    //Making the field linked list
    Fields fieldList;

    //Player picture textures
    Texture texCharA, texCharB, texCharC, texCharD, texCharE,texCharF;
    //Texture texes[6] = {texAhmad, texAmanda, texKevin, texCarl, texSteve};

    Texture texBrickFrog;

    int myOwnPlayerNumber = 0;



    explicit GameManager(int playersToMake);
    //Creating a new player
    Player createPlayer(string tempName, Texture tempTex, Texture tempBrickTex, int playerID, field * pos);

    Player getPlayerByID(int ID);

    //Rolling the dice for the current player
    void roll();

    Sprite drawPlayer(int curPlayer);
    Sprite drawPlayerPic(int curPlayer);

    Sprite drawPlayerShadow(int curPlayer);

    bool initGame();

    //simple mutex stuff;
    bool isLocked();
    bool lock();
    bool unlock();
    void network();
    GameManager() = default;



    void addToCue(char *newMsg, int sizeOfMsg);
};



#endif //PCSS2017_GAMEMANAGER_H
