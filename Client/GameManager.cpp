#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Fields.h"
#include "Player.h"
#include "Dice.cpp"
#include "Server/Server.h"
#include "Client.h"
#include<sys/socket.h>    //socket
#include<arpa/inet.h>
#include "MainMenu.cpp"
#include "Lobby.h"



class GameManager {

public:

    thread serverThread, clientThread;

    int sock;

    struct sockaddr_in server;

    Server server1 = Server(6);
    Client client1;
    MainMenu menu;
    Lobby lobby;

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

    GameManager() = default;

    explicit GameManager(int playersToMake) {
        if(!texCharA.loadFromFile("Client/Sprites/player_icons/charA.png") || !texCharB.loadFromFile("Client/Sprites/player_icons/charB.png") || !texCharC.loadFromFile("Client/Sprites/player_icons/charC.png") || !texCharD.loadFromFile("Client/Sprites/player_icons/charD.png") ||!texCharE.loadFromFile("Client/Sprites/player_icons/charE.png")||!texCharF.loadFromFile("Client/Sprites/player_icons/charF.png")) {
            cout << "Error loading player textures";
        }
        if(!texBrickFrog.loadFromFile("Client/Sprites/spr_frogTemp.png")) {
            cout << "Error loading player brick textures";
        }

        //Setting up the fields
        fieldList.setupFields(NUMBER_OF_FIELDS);


        players[0] = createPlayer("Me", texBrickFrog, texBrickFrog, myOwnPlayerNumber, fieldList.getHead());
        players[2] = createPlayer("playertwo", texBrickFrog, texBrickFrog, 2, fieldList.getHead());
        players[1] = createPlayer("playerone", texBrickFrog, texBrickFrog, 1, fieldList.getHead());

    }
    //Creating a new player
    Player createPlayer(string tempName, Texture tempTex, Texture tempBrickTex, int playerID, field * pos) {
        Player tempPlayer = Player(tempName, tempTex, tempBrickTex, playerID, pos);
        return tempPlayer;
    }

    //Rolling the dice for the current player
    void roll() {
        //Send roll to server

    }

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
    Sprite drawPlayer(int curPlayer) {
        Sprite playerSpr;
            if(players[curPlayer].hasPlayer) {
                playerSpr = players[curPlayer].display();
            }
        return playerSpr;
    }
    Sprite drawPlayerPic(int curPlayer) {
        Sprite playerSpr;
        if(players[curPlayer].hasPlayer) {
            playerSpr = players[curPlayer].displayPic();
        }
        return playerSpr;
    }

    Sprite drawPlayerShadow(int curPlayer) {
        Sprite playerSpr;
        if(players[curPlayer].hasPlayer) {
            playerSpr = players[curPlayer].displayShadow();
        }
        return playerSpr;
    }

    bool initGame() {

        int answer;
        answer = menu.start();

        switch (answer) {
            case 0:
                return false;
                break;
            case 1:
                //Making new game manager with desired amount of players
                cout << "How many players will be playing?" << endl;
                int amountOfPlayers;
                amountOfPlayers = menu.getPlayerNum();
                if (amountOfPlayers <= 6 && amountOfPlayers > 0) {
                    string ipAddr = "127.0.0.1";
                    const char* ip = ipAddr.c_str();
                    //client1.ipAddr = ip;
                    //server1.ipAddr = ip;
                    //Creating a new server object
                    serverThread = thread([this]{ server1.start();});

                    puts("Server started\n");
                }
                while(!server1.isStarted()); // wait for server to start
                client1.iWannaHost(); // allows us to host the game

                break;
            case 2:
                std::string ipAddr;
                puts("What's the ip of the the server you want to join? (xxx.xxx.xxx.xxx)\n");
                ipAddr = menu.ipAddressGet();
                if(ipAddr.length() < 7) {
                    ipAddr = "127.0.0.1";
                }
                const char* ip = ipAddr.c_str();
                //client1.ipAddr = ip;

                break;

        }
        clientThread = thread([this]{ client1.start();});
        players[myOwnPlayerNumber].setPic(lobby.start());

        players[1].setPic(rand()%6);
        players[2].setPic(rand()%6);

        return true;
    }


};
