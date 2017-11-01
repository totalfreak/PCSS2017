

#include "Server.h"

Server::Server(int maxNrOfPlayers) {
    //setup a server that can host up to maxNrOfPlayers
    maxPlayers = maxNrOfPlayers;
    clients =  new ClientSock[maxPlayers];
    recvThreads = new thread[maxPlayers];

    for(int i = 0 ; i < maxNrOfPlayers; i++){   // set all the client spots as empty
        clients[i].client = -1;
    }
}
void Server::Listner(ClientSock aClient) {
    //when ever a new client is connected a listner thread is started for them
    //it is a loop that checks if there is a new msg, and if there is, tells the
    //talker thread to send it to all other clients
    int ReceivedBytes;
    cout << "LISTNER: new listner of a socket:" << aClient.client<< endl;
    while(started && aClient.client != -1){ // so long as the server is started and the client is connected
            char buffer[1024]; //
            ReceivedBytes = recv(aClient.client , buffer , 1024 ,0);    // recv from the client into a buffer
            if(ReceivedBytes != 0){ // if we get some data
                memcpy(aClient.recvMessage,buffer,1024);    // save it for the client
                //cout << "LISTNER: i received data from client : " << aClient.client << " : " << aClient.recvMessage << endl ;
                *aClient.msgSent = false;   // tell the talker thread that there is a new msg from the client
            }

    }
    cout << " i lost connection to" << aClient.client << "or the server is offline"<< endl;
}

void Server::AcceptClients() {
    // loop that waits finds and empty spot then
    // waits for a client to connect then
    //  then starts a thread for receiving form the new client
    while(started){
        int emptySpot = -1; // if theres no client in a spot it is -1
        for(int i =  0 ; i < maxPlayers ; i++){ // loop through all posible spots
            if(clients[i].client == -1){    // if there is no client the spot must be empty
                emptySpot = i; // save the position where theres an empty spot
                break;
            }
        }

        if(emptySpot == -1){    // if we find no spots do nothing
            continue;
        }
        cout << "ACCEPT: waiting for clients to connect " << endl;

        //wait for a new client
        clients[emptySpot].client = accept(serverSock,(struct sockaddr *)& clients[emptySpot],& clients[emptySpot].theriSize);
        //wwhen connected make a reference to the client
        ClientSock * test = &clients[emptySpot];
        //start a thread for the new client to recv from it
        recvThreads[emptySpot] = thread([this, test] {this->Listner(*test); } );
        cout << "ACCEPT: new client conected they are in spot:" << emptySpot<<  endl;
    }
}

void Server::Talker() {
    // while loop, that looks at each client, then if theres a new msg from them, send it to all clients
    while(started) {
        for (int i = 0; i < maxPlayers; i++) {  // loop through all client spots
            if (clients[i].client == -1) { continue; }  // if there is client in the spot do nothing

            if(*clients[i].msgSent == false) {  // if theres no new msg form the client do nothing

                //if ther is send to all connected clients
                for(int j = 0 ; j < maxPlayers ; j++) {

                    if(clients[j].client == -1){ continue; }
                    cout << "TALKER: i am sending the message " << clients[i].recvMessage << "to client " << i << " to client nr " << j<< endl;

                    clients[i].recvMessage[0] =  '0' + i;
                    send(clients[j].client, clients[i].recvMessage, 1024, 0);
                }

                *clients[i].msgSent = true;
            }
        }
    }
}

void Server::stop() {
    started == false;
}

bool Server::isStarted() {
    return started;
}

int Server::start() {

    //creates sockets, binds it and starts to listen on it
    struct sockaddr_in server_addr;
    socklen_t size;

    serverSock = socket(AF_INET, SOCK_STREAM,0);    //create TCP socket for ip4

    if (serverSock < 0) {
        cout << "SERVER:Error establishing socket ..." << endl;
        exit(-1);
    }

    cout << "SERVER:Socket server has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(port);


    if ((bind(serverSock, (struct sockaddr*) &server_addr, sizeof(server_addr))) < 0) {
        cout << "SERVER: Error binding connection, the socket has already been established..." << endl;
        exit(-1);
    }

    size = sizeof(server_addr);
    listen(serverSock, 1);
    cout << "SERVER: Looking for clients..." << endl;

    //then allow the threads to loop
    started = true;
    accThread = thread([this] { this->AcceptClients(); });  //used to accept clients and start a RECV thread for each of them
    sendThread = thread([this] {this->Talker();});          // used to send to all clients

}


