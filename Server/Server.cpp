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

    void error(const char *msg) {
        perror(msg);
        exit(1);
    }



    void setupServer(int amountOfPlayers) {
        //Creating the socket
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);

        if (socket_desc == -1) {
            error("Could not create socket");
        }
        puts("Socket created");

        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(2222);

        //Bind the socket
        bind(socket_desc, (struct sockaddr *) &server, sizeof(server));

        puts("bind done");

        listen(socket_desc, 5);

        puts("Waiting for new connections");

        c = sizeof(struct sockaddr_in);

        runServerLoop();

        if (client_sock < 0) {
            error("Accepting client failed");
        }
    }



public:
    explicit Server(int amountOfPlayers) {
        setupServer(amountOfPlayers);
    }
    void sendActionTakenToEveryone(int playerWhoDidIt, char action) {

    }
    void *connection_handler(void *socket_desc) {
        //Get the socket descriptor
        int sock = *(int *) socket_desc;
        int readSize;
        char *message, clientMessage[2000];
        int playerNumber = 0;

        while ((readSize = static_cast<int>(recv(sock, clientMessage, 2000, 0))) > 0) {
            //Making a stringstream
            stringstream ss;
            // 0 = playerNumber
            // 1 = action
            //ACTIONS
            // r = roll
            // t = turn taken
            // p = No action, just sending the player number
            if(clientMessage[1] == 'r') {
                ss << "Player " << clientMessage[0] << " has rolled the dices";
            } else if(clientMessage[1] == 't') {
                ss << "Player " << clientMessage[0] << " has taken their turn";
            } else if(clientMessage[1] == 'p'){
                playerNumber = clientMessage[0];
            }
            //Making a char array with the exact size of the string
            char msg[ss.str().size()];
            //Copying the stringstream into the char array
            strcpy(msg, ss.str().c_str());
            //Sending the message back
            write(sock, msg, strlen(msg));
            //Resetting message
            bzero(clientMessage, 1999);
        }

        if (readSize == 0) {
            puts("Client disconnected");
            //Deleting the leaving player from socket vector
            connectedSockets.erase(connectedSockets.begin() + (playerNumber-1));
            fflush(stdout);
        } else if (readSize == -1) {
            perror("recv failed");
        }

        //Close the socket
        //close(sock);
        //Free the socket pointer
        free(socket_desc);

        return nullptr;
    }

    void runServerLoop() {
        //When a new connection has been accepted, make a thread for it
        while ((client_sock = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &c))) {
            puts("New connection accepted");

            //pthread_t sniffer_thread;
            new_sock = (int *) malloc(1);
            *new_sock = client_sock;

            //Creating the thread
            //TODO Fix crashing, and fucking fix C++
                //thread t(&Server::connection_handler, (void *)&client_sock);
                //t.join();
            /*if (pthread_create(&sniffer_thread, nullptr, &Server::connection_handler, (void *) new_sock) < 0) {
                perror("could not create thread");
            }*/
            puts("Handler assigned for new thread");
            connectedSockets.push_back(*new_sock);
        }
    }
};



