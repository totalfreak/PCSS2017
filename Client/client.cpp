#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "constants.cpp"
#include "Server/Server.cpp"
#include "GameManager.cpp"




#include "Field.cpp"

using namespace std;
using namespace sf;


GameManager gameManager;
bool gameStarted = false;
bool lobbyMade = false;
int sock;
struct sockaddr_in server;
char message[1000], serverReply[2000];

void error(const char *msg) {
    perror(msg);
    exit(0);
}



void initGame() {
    //Temp server connection here
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        perror("Could not create socket");
    }
    puts("Socket created");

    char answer;
    cout << "Do you want to host a server, or join one?\n1: Host server\n2: Join server" << endl;
    cin >> answer;
    switch (answer) {
        case '1':
            //Making new game manager with desired amount of players
            cout << "How many players will be playing?" << endl;
            int amountOfPlayers;
            cin >> amountOfPlayers;
            if (amountOfPlayers <= 6 && amountOfPlayers > 0) {
                //Creating a new server object
                Server server1(amountOfPlayers);

                server.sin_addr.s_addr = inet_addr("127.0.0.1");
                server.sin_family = AF_INET;
                server.sin_port = htons( 2222 );

                //Connect to server
                if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
                    error("connect failed. Error");
                }
                puts("Connected\n");
                gameManager = GameManager(amountOfPlayers);
                gameManager.currentPlayer = 1;
                gameManager.players[0].setPlayersTurn();
                lobbyMade = true;
            } else {
                cout << "Try one more time" << endl;
                initGame();
            }
            break;
        case '2':
            std::string ipAddr;
            puts("What's the ip of the the server you want to join? (xxx.xxx.xxx.xxx)\n");
            std::getline(std::cin, ipAddr);
            if(ipAddr.length() < 7) {
                ipAddr = "127.0.0.1";
            }
            const char* ip = ipAddr.c_str();
            server.sin_addr.s_addr = inet_addr(ip);
            server.sin_family = AF_INET;
            server.sin_port = htons( 2222 );

            //Connect to server
            if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
                error("connect failed. Error");
            }
            puts("Connected\n");

            gameStarted = true;

            //Do some server stuff here.
            break;
    }
}


void setDicePos() {
    gameManager.die.diceSprites[0].setPosition(100, 100);
    gameManager.die.diceSprites[1].setPosition(150, 100);
}

int main() {
    //Seeding random function
    srand (time(NULL));

    if(!gameStarted && !lobbyMade) {
        initGame();
    }

    //Making window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dice game");

    //Temp background location
    Texture bgTex;
    Sprite bgSpr;

    //Loading the background image
    if(!bgTex.loadFromFile("Client/Sprites/spr_bgFrame.jpg")) {
        cout << "Error loading BG texture";
    }
    bgSpr.setTexture(bgTex);


    //Making the field linked list
    Fields fieldList;
    fieldList.setupFields(fieldList, NUMBER_OF_FIELDS);

    // run the program as long as the window is open
    while (window.isOpen())
    {

        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            //Checking for left mouse press
            if(event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Button::Left) {
                    gameManager.takeTurn();
                }
            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }



        Sprite dice1Spr, dice2Spr;

        window.clear(Color::Black);
        window.draw(bgSpr);

        fieldList.display(window, fieldList, NUMBER_OF_FIELDS);

        //Drawing the dices
        setDicePos();
        window.draw(gameManager.die.diceSprites[0]);
        window.draw(gameManager.die.diceSprites[1]);
        for (int i = 0; i < 6; i++) {
            window.draw(gameManager.drawPlayer(i));
        }

        window.display();

    }

    return 0;
}





