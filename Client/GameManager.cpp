#include "GameManager.h"

void GameManager::network() {

    if(!(client1->recvMsgDealtWith == false && client1->isStarted())){return;}
    //otherwise there must be a new msg to deal with

    cout << "we got to char" << endl;
    char msg[1024];
    cout << "copying" << endl;
    memcpy(msg,client1->getMsg(),1024); // copy the msg
    client1->recvMsgDealtWith = true;    // tell the client that we are ready to receive a new msg
    cout << "stringing" << endl;
    // read the arguments from the received msg
    string arg[3];
    arg[0] = "%";
    arg[1] = "%";
    arg[2] = "%";
    cout << "reading args" << endl;
    char * reader = strtok(msg,":");
    if(reader != nullptr){ arg[0] = reader;}
    reader = strtok(NULL,":");
    if(reader != nullptr){ arg[1] = reader;}
    reader = strtok(NULL,":");
    if(reader != nullptr){ arg[2] = reader;}
    cout << arg[0] << ":" << arg[1] << ":" << arg[2]<< endl;

    cout << "got args" << endl;
    switch(arg[1].c_str()[0]){
        case 'j':{// j means that a player is joininCr
            cout << "creating new player" << endl;
            int playerNr = stoi(arg[0],0);
            players[playerNr] = createPlayer(arg[2],texBrickFrog,texBrickFrog,playerNr,fieldList.getHead());
            cout << "created new player: " << playerNr << endl;
            client1->tellThatIExist();
            break;
        }
        case 'm':{

            break;
        }
        case 'u':{
            int playerNr = stoi(arg[0],0);
            if(!players[playerNr].hasPlayer){
                players[playerNr] = createPlayer(arg[2],texBrickFrog,texBrickFrog,playerNr,fieldList.getHead());
                cout << "created new player: " << playerNr << endl;
            }
            break;
        }
        case 'r':{ // new roll
            int playerNr = stoi(arg[0],0);
            cout << "Player " << playerNr << " rolled " << arg[2] << endl;
            break;
        }
        case 't':{ // pass turn
            int playerNr = stoi(arg[0],0);
            cout << "player " << playerNr << " has ended their turn." << endl;
        }

    }

}

GameManager::GameManager(int playersToMake) {

    lobby = new Lobby(this); //create a new lobby with a reference to this game manger
    client1 = new Client(this);

    if(!texCharA.loadFromFile("Client/Sprites/player_icons/charA.png") || !texCharB.loadFromFile("Client/Sprites/player_icons/charB.png") || !texCharC.loadFromFile("Client/Sprites/player_icons/charC.png") || !texCharD.loadFromFile("Client/Sprites/player_icons/charD.png") ||!texCharE.loadFromFile("Client/Sprites/player_icons/charE.png")||!texCharF.loadFromFile("Client/Sprites/player_icons/charF.png")) {
        cout << "Error loading player textures";
    }
    if(!texBrickFrog.loadFromFile("Client/Sprites/spr_frogTemp.png")) {
        cout << "Error loading player brick textures";
    }

    //Setting up the fields
    fieldList.setupFields(NUMBER_OF_FIELDS);

}

Player GameManager::createPlayer(string tempName, Texture tempTex, Texture tempBrickTex, int playerID, field *pos) {
    Player tempPlayer = Player(tempName, tempTex, tempBrickTex, playerID, pos);
    return tempPlayer;
}

void GameManager::roll() {
    //Send roll to server
    client1->roll(die.roll());
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
            client1->iWannaHost(); // allows us to host the game

            break;
        case 2:
            std::string ipAddr;
            //puts("What's the ip of the the server you want to join? (xxx.xxx.xxx.xxx)\n");
            //ipAddr = menu.ipAddressGet();
            //if(ipAddr.length() < 7) {
              //  ipAddr = "127.0.0.1";
            //}
            const char* ip = ipAddr.c_str();
            //client1.ipAddr = ip;

            break;

    }

    string name;
    name = menu.ipAddressGet();
    client1->changeName(name);
    clientThread = thread([this]{ client1->start();});
    while(!client1->isStarted());

    players[myOwnPlayerNumber].setPic(lobby->start());

    players[1].setPic(rand()%6);
    players[2].setPic(rand()%6);

    return true;
}
