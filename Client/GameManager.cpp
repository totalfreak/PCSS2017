#include "GameManager.h"

void GameManager::network() {
    if(client1.recvMsgDealtWith){return;}
    //otherwise there must be a new msg to deal with

    char * ptr = strtok(client1.getMsg(), ":");

    while(ptr != NULL){
        ptr = strtok(nullptr, ":");
        cout << ptr << endl;
    }

}

GameManager::GameManager(int playersToMake) {

    lobby = new Lobby(this); //create a new lobby with a reference to this game manger

    if(!texCharA.loadFromFile("Client/Sprites/player_icons/charA.png") || !texCharB.loadFromFile("Client/Sprites/player_icons/charB.png") || !texCharC.loadFromFile("Client/Sprites/player_icons/charC.png") || !texCharD.loadFromFile("Client/Sprites/player_icons/charD.png") ||!texCharE.loadFromFile("Client/Sprites/player_icons/charE.png")||!texCharF.loadFromFile("Client/Sprites/player_icons/charF.png")) {
        cout << "Error loading player textures";
    }
    if(!texBrickFrog.loadFromFile("Client/Sprites/spr_frogTemp.png")) {
        cout << "Error loading player brick textures";
    }

    //Setting up the fields
    fieldList.setupFields(NUMBER_OF_FIELDS);


    //players[0] = createPlayer("Me", texBrickFrog, texBrickFrog, myOwnPlayerNumber, fieldList.getHead());
    //players[2] = createPlayer("playertwo", texBrickFrog, texBrickFrog, 2, fieldList.getHead());
    //players[1] = createPlayer("playerone", texBrickFrog, texBrickFrog, 1, fieldList.getHead());

}

Player GameManager::createPlayer(string tempName, Texture tempTex, Texture tempBrickTex, int playerID, field *pos) {
    Player tempPlayer = Player(tempName, tempTex, tempBrickTex, playerID, pos);
    return tempPlayer;
}

void GameManager::roll() {
    //Send roll to server

}

Sprite GameManager::drawPlayer(int curPlayer) {
    Sprite playerSpr;
    if(players[curPlayer].hasPlayer) {
        playerSpr = players[curPlayer].display();
    }
    return playerSpr;
}

Sprite GameManager::drawPlayerPic(int curPlayer) {
    Sprite playerSpr;
    if(players[curPlayer].hasPlayer) {
        playerSpr = players[curPlayer].displayPic();
    }
    return playerSpr;
}

Sprite GameManager::drawPlayerShadow(int curPlayer) {
    Sprite playerSpr;
    if(players[curPlayer].hasPlayer) {
        playerSpr = players[curPlayer].displayShadow();
    }
    return playerSpr;
}

bool GameManager::initGame() {

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
    players[myOwnPlayerNumber].setPic(lobby->start());

    players[1].setPic(rand()%6);
    players[2].setPic(rand()%6);

    return true;
}
