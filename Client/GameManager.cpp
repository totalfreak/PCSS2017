#include "GameManager.h"

void GameManager::network() {

    if(!lock()){
        cout << "CLIENT NETWORK: i could not get a lock " << endl;
        return;
    } // if we cant lock the program to nothing
    cueNode * ptr = cueHead;
    while(ptr != nullptr){
        cout << ptr->msg << endl;
        ptr = ptr->next;
    }
    while(cueHead!= nullptr) { // do this until the cue is empty

        cueNode * temp = cueHead;
        //read data at head in cue
        char msg[1024];
        memcpy(msg, temp->msg, 1024); // copy the msg

        // read the arguments from the received msg
        string arg[3];
        arg[0] = "%";
        arg[1] = "%";
        arg[2] = "%";
        char *reader = strtok(msg, ":");
        if (reader != nullptr) { arg[0] = reader; }
        reader = strtok(NULL, ":");
        if (reader != nullptr) { arg[1] = reader; }
        reader = strtok(NULL, ":");
        if (reader != nullptr) { arg[2] = reader; }
        cout << arg[0] << ":" << arg[1] << ":" << arg[2] << endl;


        switch (arg[1].c_str()[0]) {
            case 'j': {// j means that a player is joininCr

                int playerNr = stoi(arg[0], 0);
                if (players[playerNr].hasPlayer) { break; } //if the player allready exists, do nothing
                players[playerNr] = createPlayer(arg[2], texBrickFrog, texBrickFrog, playerNr, fieldList.getHead());
                cout << "created new player: " << playerNr << endl;
                client1->tellThatIExist();
                break;
            }
            case 'm': {

                break;
            }

            case 'r': { // new roll
                int playerNr = stoi(arg[0], 0);

                cout << "Player " << playerNr << " rolled " << arg[2].at(0) << " and " << arg[2].at(1)
                     << " for a total of " << arg[2].at(2) << arg[2].at(3) << endl;
                int rolled[2];
                rolled[0] = arg[2].at(0) - '0';
                rolled[1] = arg[2].at(1) - '0';
                die.setTex(rolled);
                break;
            }
            case 't': { // pass turn
                int playerNr = stoi(arg[0], 0);
                cout << "player " << playerNr << " has ended their turn." << endl;
            }
            case 'u': { // pass turn

                int playerNr = stoi(arg[0], 0);
                if (players[playerNr].hasPlayer) { break; } //if the player allready exists, do nothing
                players[playerNr] = createPlayer(arg[2], texBrickFrog, texBrickFrog, playerNr, fieldList.getHead());

            }

        }

        //set a new head in the cue
        cueHead = cueHead->next;
        if(cueHead == nullptr){
            cueTail = nullptr;
        }

        // free the memmory used to store the nsg

        delete temp;
    }

    // now that the cue is empty we can unlock the cue, so the client can add the things it receives to it
    unlock();
}

GameManager::GameManager(int playersToMake) {

    lobby = new Lobby(this); //create a new lobby with a reference to this game manger
    client1 = new Client(this);

    cueHead = nullptr;
    cueTail = nullptr;

    locked = false;

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


    client1->configureClient();
    clientThread = thread([this]{ client1->start();});
    while(!client1->isStarted());

    players[myOwnPlayerNumber].setPic(lobby->start());

    return true;
}

bool GameManager::isLocked() {
    return locked;
}

bool GameManager::lock() {
    if(!locked){
        locked = true;
        return true;
    }
    return false;
}

bool GameManager::unlock() {
    locked = false;
}

void GameManager::addToCue(char * newMsg, int sizeOfMsg){

    while(lock()); //make sure nobody is messing with the list

    //make a new node and copy the msg into it
    cueNode * tempNode = new cueNode;
    tempNode->next = nullptr;

    memcpy(tempNode->msg, newMsg, sizeOfMsg);

    //add it to the list
    if(cueHead == nullptr && cueTail == nullptr){
        cueHead = tempNode;
        cueTail = tempNode;
    }else{
        cueTail->next = tempNode;
        cueTail = tempNode;
    }

    unlock(); //allow others acess to the list;

}

Player GameManager::getPlayerByID(int ID) {
    Player temp;
    for(int i = 0; i < sizeof(players); i++){
        if(players[i].myID == ID){
            temp = players[i];
            break;
        }
    }
    return temp;
}
