//
// Created by rasmus on 10/27/17.
//

#ifndef PCSS2017_CLIENT_H
#define PCSS2017_CLIENT_H

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
#include "constants.h"
#include "GameManager.h"

class Lobby;
class GameManager;

using namespace std;

class Client {


    bool isHost = false;
    bool started = false;


private:
    GameManager * game;
    int sock;   // tell the computer which socket we are sending on
    thread sendThread;  // thread used to send to server
    thread recvThread;  // thread for revcving from server
    char msgToBeSent[1024];

    bool hasMsgBeenSent = true; // tells the client wheather or not the msg has been sent before
    char name[16] = "no name";

public:

    Client(GameManager *creator);
    void start();
    void listen();
    void sendMessage(char* msg, int size);
    void talk();
    void iWannaHost();

    void informOfConnection();
    void roll(char* arr);

    bool isStarted() const;

    void changeName(string newName);
    void tellThatIExist();
};

#endif //PCSS2017_CLIENT_H
