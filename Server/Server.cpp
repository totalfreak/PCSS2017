//Main server program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sstream>
#include <iostream>
#include <mutex>
#include <SFML/Graphics.hpp>

using namespace std;
void *sendAccept(void *);

void error(const char *msg) {
    perror(msg);
    exit(1);
}

//the thread connection handler
void *connection_handler(void *);

int main() {

    int socket_desc, client_sock, c, *new_sock;
    struct sockaddr_in server, client;

    //Creating the socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc == -1) {
        error("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 2222 );

    //Bind the socket
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    listen(socket_desc, 5);

    puts("Waiting for new connections");

    c = sizeof(struct sockaddr_in);

    while((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))) {
        puts("New connection accepted");

        pthread_t sniffer_thread;
        new_sock = (int*) malloc(1);
        *new_sock = client_sock;

        //Creating the thread
        if(pthread_create(&sniffer_thread, nullptr, connection_handler, (void*) new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }
        puts("Handler assigned for new thread");
    }

    if(client_sock < 0) {
        perror("Accepting client failed");
        return 1;
    }

    return 0;
}

void *connection_handler(void *socket_desc) {
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int readSize;
    char *message, clientMessage[2000];

    while((readSize = static_cast<int>(recv(sock, clientMessage, 2000, 0))) > 0) {
        //Making a stringstream
        stringstream ss;
        ss << "Fuck youuu";
        //Making a char array with the exact size of the string
        char msg[ss.str().size()];
        //Copying the stringstream into the char array
        strcpy(msg, ss.str().c_str());
        //Sending the message back
        write(sock, msg, strlen(msg));
        //Resetting message, just in case
        bzero(clientMessage, 1999);
    }

    if(readSize == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if(readSize == -1) {
        perror("recv failed");
    }

    //Close the socket
    //close(sock);
    //Free the socket pointer
    free(socket_desc);

    return nullptr;
}
