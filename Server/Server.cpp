

#include "Server.h"

Server::Server(int maxNrOfPlayers) {
    maxPlayers = maxNrOfPlayers;
    clients =  new ClientSock[maxPlayers];

    for(int i = 0 ; i < maxPlayers ; i++){
        clients[i].client = -1;
    }


    //for setting up server
    struct addrinfo serverHints;
    struct addrinfo *serverInfo;
    struct addrinfo *p;


    memset(&serverHints, 0, sizeof(serverHints)); // get hints about the server

    serverHints.ai_family = AF_UNSPEC;
    serverHints.ai_socktype = SOCK_STREAM;
    serverHints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, port, &serverHints, &serverInfo) != 0) {
        cout << "could not get addres" << endl;
    }

    for (p = serverInfo; p != NULL; p = p->ai_next) {
        if (serverSock = socket(p->ai_family, p->ai_socktype, p->ai_protocol) == -1) {
            cout << "one addr failed ";
            continue;
        }
        cout << "One addr worked : ";
        if (bind(serverSock, p->ai_addr, p->ai_addrlen) == -1) {
            close(serverSock);
            cout << "but did not bind " << endl;
            continue;
        }
        cout << "and it did bind " << endl;
        break;
    }
    freeaddrinfo(serverInfo); // all done with this structure

    if (p == NULL) {
        exit(1);
    }

    if (listen(serverSock, 10) == -1) {
        cout << "listen() fucked up somehow " << endl;
    }
}

void Server::Listner() {
    int ReceivedBytes;
    while(started){
        for(int i = 0; i < maxPlayers; i++) {

            if(clients[i].client != -1 && clients[i].msgSent == true) {
                ReceivedBytes = recv(clients[i].client , clients[i].recvMessage , 1024 ,0);
                if(ReceivedBytes != 0){
                    cout << " i received data from client : " << i << " : " << clients[i].recvMessage << endl ;
                    clients[i].msgSent = false;
                }
            }
        }
    }

}

void Server::AcceptClients() {
    while(started){
        int emptySpot = -1;
        for(int i =  0 ; i < maxPlayers ; i++){
            if(clients[i].client == -1){
                emptySpot = i;
                break;
            }
        }

        if(emptySpot == -1){
            continue;
        }
        clients[emptySpot].client = accept(serverSock,(struct sockaddr *)& clients[emptySpot],& clients[emptySpot].theriSize);
        cout << "client connected" << endl;
    }
}

void Server::Talker() {
    while(started) {
        for (int i = 0; i < maxPlayers; i++) {
            if (clients[i].client == -1) { continue; }
            if(clients[i].msgSent == false) {

                //send to all connected clients
                for(int j = 0 ; j < maxPlayers ; j++) {
                    if(clients[j].client == -1){ continue; }
                    send(clients[j].client, clients[i].recvMessage, 1024, 0);
                }

                clients[i].msgSent = true;
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
    started = true;
    accThread = thread([this] { this->AcceptClients(); });
    recvThread = thread([this] {this->Listner();});
    sendThread = thread([this] {this->Talker();});

    accThread.join();
    recvThread.join();
    sendThread.join();
}


