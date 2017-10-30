#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Fields.h"
#include "Player.h"
#include "Dice.cpp"
#include "Server/Server.h"
#include "client.h"
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
    Texture texAhmad, texAmanda, texKevin, texCarl, texSteve;
    Texture texes[6] = {texAhmad, texAmanda, texKevin, texCarl, texSteve};

    Texture texBrickFrog;

    int myOwnPlayerNumber = 1;

    GameManager() = default;

    explicit GameManager(int playersToMake) {
        if(!texAhmad.loadFromFile("Client/Sprites/player_icons/Ahmad.png") || !texAmanda.loadFromFile("Client/Sprites/player_icons/Amanda.png") || !texKevin.loadFromFile("Client/Sprites/player_icons/Kevin.png") || !texCarl.loadFromFile("Client/Sprites/player_icons/Carl.png") ||!texSteve.loadFromFile("Client/Sprites/player_icons/Steve.png")) {
            cout << "Error loading player textures";
        }
        if(!texBrickFrog.loadFromFile("Client/Sprites/spr_frogTemp.png")) {
            cout << "Error loading player brick textures";
        }

        //Setting up the fields
        fieldList.setupFields(fieldList, NUMBER_OF_FIELDS);

        //server1.start();

        //cout << "Enter a name for player " << i+1 <<  endl;
        //string desiredName; cin >> desiredName;
        //players[i] = createPlayer(desiredName, texes[i], texBrickFrog, i, fieldList.getHead());

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
                break;
            case 2:
                std::string ipAddr;
                puts("What's the ip of the the server you want to join? (xxx.xxx.xxx.xxx)\n");
                std::getline(std::cin, ipAddr);
                if(ipAddr.length() < 7) {
                    ipAddr = "127.0.0.1";
                }
                const char* ip = ipAddr.c_str();
                //client1.ipAddr = ip;

                break;

        }
        clientThread = thread([this]{ client1.start();});
        lobby.start();
        return true;
    }
};
