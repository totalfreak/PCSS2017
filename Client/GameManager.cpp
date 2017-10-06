#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.cpp"
#include "Dice.cpp"

class GameManager {

    /*
    Player Steve("Steve",textureSteve);

    Player currentPlayer("Steve",textureSteve);
    srand (time(NULL));

    switch (rand()%5){
        case 1:
            currentPlayer = Steve;
        break;
        case 2:
            currentPlayer = Ahmad;
        break;
        case 3:
            currentPlayer = Amanda;
        break;
        case 4:
            currentPlayer = Carl;
        break;
        case 5:
            currentPlayer = Kevin;
        break;
    }
    */


public:

    Dice die = Dice();
    Player player1, player2, player3, player4, player5, player6;
    Player players[6] = {player1, player2, player3, player4, player5, player6};

    Texture texAhmad, texAmanda, texKevin, texCarl, texSteve;
    Texture texes[6] = {texAhmad, texAmanda, texKevin, texCarl, texSteve};

    Texture texBrickFrog;

    int currentPlayer = 1;

    int playersInGame;

    GameManager() = default;
    explicit GameManager(int playersToMake) {
        if(!texAhmad.loadFromFile("Client/Sprites/player_icons/Ahmad.png") || !texAmanda.loadFromFile("Client/Sprites/player_icons/Amanda.png") || !texKevin.loadFromFile("Client/Sprites/player_icons/Kevin.png") || !texCarl.loadFromFile("Client/Sprites/player_icons/Carl.png") ||!texSteve.loadFromFile("Client/Sprites/player_icons/Steve.png")) {
            cout << "Error loading player textures";
        }
        if(!texBrickFrog.loadFromFile("Client/Sprites/spr_frogTemp.png")) {
            cout << "Error loading player brick textures";
        }

        //Making the desired amount of players
        for (int i = 0; i < playersToMake; ++i) {
            cout << "Enter a name for player " << i+1 <<  endl;
            string desiredName; cin >> desiredName;
            players[i] = createPlayer(desiredName, texes[i], texBrickFrog);
        }
    }
    //Creating a new player
    Player createPlayer(string tempName, Texture tempTex, Texture tempBrickTex) {
        Player tempPlayer = Player(tempName, tempTex, tempBrickTex);
        return tempPlayer;
    }

    void takeTurn() {
        //Making sure only players that are here and hasn't played yet can play
        if(!players[currentPlayer - 1].turnTaken && players[currentPlayer - 1].isPlayersTurn && players[currentPlayer - 1].hasPlayer) {
            roll();
        }
    }

    void roll() {
        //If the turn hasn't been taken, then roll
        if(!players[currentPlayer - 1].turnTaken) {
            int move = die.roll();
            //Move the player the rolled amount
            players[currentPlayer - 1].movePlayer(move);
            //Do whatever is on the landed field
            players[currentPlayer - 1].chooseAction();
            //Next turn
            nextTurn();
        }
    }

    void nextTurn() {
        //If there are no next player to go to, then go to beginning of array of players
        if(players[currentPlayer].hasPlayer) {
            currentPlayer++;
            players[currentPlayer - 1].setPlayersTurn();
        } else {
            currentPlayer = 1;
            players[currentPlayer - 1].setPlayersTurn();
        }

    }

};
