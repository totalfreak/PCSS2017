//
// Created by simone on 10/20/17.
//

#ifndef PCSS2017_SERVER_H
#define PCSS2017_SERVER_H
#pragma once
//Main server server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <sstream>
#include <mutex>
#include <vector>
#include <algorithm>


using namespace std;

class Server {

    int currentPlayer;

    vector<int> connectedSockets;

    int socket_desc, client_sock, c, *new_sock;
    struct sockaddr_in server, client;

    //void *connection_handler(void *socket_desc);

    void error(const char *msg);



    void setupServer(int amountOfPlayers);



public:
    explicit Server(int amountOfPlayers);
    void sendActionTakenToEveryone(int playerWhoDidIt, char action);
    void *connection_handler(void *socket_desc);

    void runServerLoop();
};



#endif //PCSS2017_SERVER_H
