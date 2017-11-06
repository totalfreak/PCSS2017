

#include "Server.h"
#include <string>
Server::Server(int maxNrOfPlayers) {
    //Set up a server that can host up to maxNrOfPlayers
    maxPlayers = maxNrOfPlayers;
    clients =  new ClientSock[maxPlayers];
    recvThreads = new std::thread[maxPlayers];

    for(int i = 0 ; i < maxNrOfPlayers; i++){   //Set all the client spots as empty
        clients[i].client = -1;
    }
    currentPlayerTurn = 0;
    std::cout << "TRNORD: it is now player : 0's turn"<<std::endl;
}
void Server::Listner(ClientSock aClient) {
    /* Whenever a new client is connected, a listner thread is started for them.
     * It is a loop that checks if there is a new msg, and if there is, it tells the
     * talker thread to send it to all other clients.
     */

    int ReceivedBytes;
    std::cout << "LISTNER: new listner of a socket:" << aClient.client<< std::endl;
    while(started && aClient.client != -1){ //As long as the server is started and the client is connected
            char buffer[1024]; //
            ReceivedBytes = recv(aClient.client , buffer , 1024 ,0);    //recv from the client into a buffer
            if(ReceivedBytes != 0){ //If we get some data
                memcpy(aClient.recvMessage,buffer,1024);    //Save it for the client
                //cout << "LISTNER: i received data from client : " << aClient.client << " : " << aClient.recvMessage << endl ;
                *aClient.msgSent = false;   //Tell the talker thread that there is a new msg from the client
            }

    }
    std::cout << " i lost connection to" << aClient.client << "or the server is offline"<< std::endl;
}

void Server::AcceptClients() {
    /* Loop that waits finds and empty spot then
     * Waits for a client to connect then
     * Then starts a thread for receiving from the new client
     */

    while(started){
        int emptySpot = -1; //If there is no client in a spot it is -1
        for(int i =  0 ; i < maxPlayers ; i++){ //Loop through all possible spots
            if(clients[i].client == -1){    //If there is no client the spot must be empty
                emptySpot = i; //Save the position where there is an empty spot
                break;
            }
        }

        if(emptySpot == -1){ //If we find no spots do nothing
            continue;
        }
        std::cout << "ACCEPT: waiting for clients to connect " << std::endl;

        //Wait for a new client
        clients[emptySpot].client = accept(serverSock,(struct sockaddr *)& clients[emptySpot],& clients[emptySpot].theriSize);
        //When connected make a reference to the client
        ClientSock * test = &clients[emptySpot];
        clients[emptySpot].isConnected = true;
        //Start a thread for the new client to recv from it
        recvThreads[emptySpot] = std::thread([this, test] {this->Listner(*test); } );
        std::cout << "ACCEPT: new client connected they are in spot:" << emptySpot<<  std::endl;
    }
}


void Server::Talker() {
    //While loop, that looks at each client, then if there is a new msg from them, send it to all clients
    while(started) {
        for (int i = 0; i < maxPlayers; i++) {  //Loop through all client spots
            if (clients[i].client == -1) { continue; }  //If there is client in the spot do nothing

           // if (clients[i].recvMessage[2] =='r' && currentPlayerTurn != i){ continue;} //If the player want to roll but it is not thier turn do nothing

            if(*clients[i].msgSent == false) {  //If there's no new msg form the client do nothing

                //If there is any msg send it to all connected clients
                for(int j = 0 ; j < maxPlayers ; j++) {

                    if(clients[j].client == -1){ continue; }
                    std::cout << "TALKER: i am sending the message " << clients[i].recvMessage << " from cli" << i << " -> cli" << j<< std::endl;

                    clients[i].recvMessage[0] =  '0' + i;
                    send(clients[j].client, clients[i].recvMessage, 1024, 0);

                }

                //if(clients[i].recvMessage[2] =='r') {nextTurn();}
                *clients[i].msgSent = true;
            }
        }
    }
}


void Server::nextTurn() {
    /*bool leaveLoop = false;

    while(!leaveLoop) {
        currentPlayerTurn++;
        if (currentPlayerTurn >= maxPlayers) { currentPlayerTurn = 0; }
        if (!clients[currentPlayerTurn].isConnected){leaveLoop = true;}
    }
    cout << "TRNORD:it is now player " << currentPlayerTurn << "'s turn";*/
}

void Server::stop() {
    started == false;
}

bool Server::isStarted() {
    return started;
}

int Server::start() {

    //Creates sockets, binds it and starts to listen on it
    struct sockaddr_in server_addr;
    socklen_t size;

    serverSock = socket(AF_INET, SOCK_STREAM,0);    //Create TCP socket for ip4

    if (serverSock < 0) {
        std::cout << "SERVER:Error establishing socket ..." << std::endl;
        exit(-1);
    }

    std::cout << "SERVER:Socket server has been created..." << std::endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(port);

    if (bind(serverSock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cout << "SERVER: Error binding connection, the socket has already been established..." << std::endl;
        exit(-1);
    }

    size = sizeof(server_addr);
    listen(serverSock, 1);
    std::cout << "SERVER: Looking for clients..." << std::endl;

    //Then allow the threads to loop
    started = true;
    accThread = std::thread([this] { this->AcceptClients(); });  //Used to accept clients and start a RECV thread for each of them
    sendThread = std::thread([this] {this->Talker();});          //Used to send to all clients

}


