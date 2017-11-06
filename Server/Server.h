//
// Created by simone on 10/20/17.
//

#ifndef PCSS2017_SERVER_H
#define PCSS2017_SERVER_H
#pragma once

#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>
#include "../Client/constants.h"

struct  ClientSock{
    int client;
    sockaddr thierAddr;
    socklen_t theriSize;
    char * recvMessage = new char[1024];
    bool * msgSent = new bool;
    bool isConnected = false;
    std::string clientName;
};

class Server {

    //Setting the server up
    int maxPlayers;
    int nrOfPlayers = 0;
    bool started = false;
    int currentPlayerTurn = -1;


    //Internet
    ClientSock * clients  ;       //All the socket the players connect to
    int serverSock;

    //Sending and receiving
    char * msg[1024];
    std::thread accThread;
    std::thread * recvThreads;
    std::thread sendThread;

public:
    const char* ipAddr;
    Server(int maxNrOfPLayers); //Setup server so and start to listen on server socket;

    int start();
    void Talker();
    void stop();
    void nextTurn();


    bool isStarted();

    void AcceptClients();

    void Listner(ClientSock aClient);
};




#endif //PCSS2017_SERVER_H
