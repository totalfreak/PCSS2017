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


class GameManager {

public:

    thread serverThread, clientThread;

    int sock;

    struct sockaddr_in server;

    Server server1 = Server(6);
    Client client1;
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

    //Rolling the dice for the current player
    void roll();

/*
    //Serverproof recursive nextTurn function
    void nextTurn(int curPlayer) {
        //If there are no next player to go to, then go to beginning of array of players
        if(players[curPlayer].hasPlayer) {
            currentPlayer++;
            players[currentPlayer - 1].setPlayersTurn();
            //If end of array has been reached, then restart
        } else if(curPlayer > 6){
            currentPlayer = 1;
            players[currentPlayer - 1].setPlayersTurn();
        } else {
            //If the end hasn't been reached, to make sure that if player 3 leaves, but player 4 and 5 are still playing
            //it should keep looking for players all the way through the loop, but still only pick up actual players
            nextTurn(curPlayer+1);
        }
    }
    */
    Sprite drawPlayer(int curPlayer);
    Sprite drawPlayerPic(int curPlayer);

    Sprite drawPlayerShadow(int curPlayer);

    bool initGame();


    void network();
    GameManager() = default;


};



#endif //PCSS2017_GAMEMANAGER_H
