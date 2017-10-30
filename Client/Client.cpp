//
// Created by rasmus on 10/27/17.
//

#include "Client.h"

Client::Client(){
    cout << "setting up Client" << endl;
    struct addrinfo *p;
    struct addrinfo socketHints;
    struct addrinfo * ClientInfo;


    memset(&socketHints, 0, sizeof(socketHints)); // get hints about the server

    socketHints.ai_family = AF_UNSPEC;
    socketHints.ai_socktype = SOCK_STREAM;
    socketHints.ai_flags = AI_PASSIVE;
    socketHints.ai_addr = 

    if (getaddrinfo(NULL, port, &socketHints, &ClientInfo) != 0) {
        cout << "could not get addres" << endl;
    }

    for (p = ClientInfo; p != NULL; p = p->ai_next) {
        if (sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol) == -1) {
            cout << "one addr failed ";
            continue;
        }
        cout << "One addr worked trying to connect: ";
        if (connect(sock , p->ai_addr, p->ai_addrlen) == -1) {
            close(sock);
            cout << "but could not connect " << endl;
            continue;
        }
        cout << "connection established " << endl;
        break;
    }
    freeaddrinfo(ClientInfo); // all done with this structure
    started = true;
}

void Client::talk() {
    int haha = 0;
    while (started) {
        if(hasMsgBeenSent = true){return ;}

        send(sock, msgToBeSent, 1024, 0);
        hasMsgBeenSent = true;

    }
}

void Client::listen() {
    cout << "im listning " << endl;
    char res[1024];
    int dataReceived;
    while (started){
        dataReceived = recv(sock, res , 1024 , 0);
        if(dataReceived != 0){
            cout << " received data " << res << endl;
        }

        //listen logic goes here

    }

}

void Client::start() {
    sendThread = thread([this]{ talk();});
    recvThread = thread([this]{ listen();});

    sendThread.join();
    recvThread.join();

}

void Client::sendMessage(char * msg, int size) {
    if(size != 1024){
        cout << "msg to large or to small use 1024" << endl;
        return;
    }
    for(int i = 0 ; i < 1024; i++) {
        *(msgToBeSent + i) = *(msg + i);
    }
    hasMsgBeenSent = false;
}