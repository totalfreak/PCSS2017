#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.cpp"
#include "Field.cpp"
#include "Player.cpp"
#include "Dice.cpp"


class GameManager {

public:

    Dice die = Dice();
    //Making the player objects and storing them in the player array
    Player player1, player2, player3, player4, player5, player6;
    Player players[6] = {player1, player2, player3, player4, player5, player6};

    //Making the field linked list
    Fields fieldList;

    //Player picture textures
    Texture texAhmad, texAmanda, texKevin, texCarl, texSteve;
    Texture texes[6] = {texAhmad, texAmanda, texKevin, texCarl, texSteve};

    Texture texBrickFrog;

    int currentPlayer = 1;


    GameManager() = default;
    explicit GameManager(int playersToMake) {
        if(!texAhmad.loadFromFile("Client/Sprites/player_icons/Ahmad.png") || !texAmanda.loadFromFile("Client/Sprites/player_icons/Amanda.png") || !texKevin.loadFromFile("Client/Sprites/player_icons/Kevin.png") || !texCarl.loadFromFile("Client/Sprites/player_icons/Carl.png") ||!texSteve.loadFromFile("Client/Sprites/player_icons/Steve.png")) {
            cout << "Error loading player textures";
        }
        if(!texBrickFrog.loadFromFile("Client/Sprites/spr_frogTemp.png")) {
            cout << "Error loading player brick textures";
        }

        //Setting up the fields
        fieldList.setupFields(fieldList, NUMBER_OF_FIELDS);

        //Making the desired amount of players
        for (int i = 0; i < playersToMake; ++i) {
            cout << "Enter a name for player " << i+1 <<  endl;
            string desiredName; cin >> desiredName;
            players[i] = createPlayer(desiredName, texes[i], texBrickFrog, i);
        }

    }
    //Creating a new player
    Player createPlayer(string tempName, Texture tempTex, Texture tempBrickTex, int playerID) {
        Player tempPlayer = Player(tempName, tempTex, tempBrickTex, playerID);
        return tempPlayer;
    }

    void takeTurn() {
        //Making sure only players that are here and hasn't played yet, can play
        if(!players[currentPlayer - 1].turnTaken && players[currentPlayer - 1].isPlayersTurn && players[currentPlayer - 1].hasPlayer) {
            roll();
        }
    }

    //Rolling the dice for the current player
    void roll() {
        //If the turn hasn't been taken, then roll
        if(!players[currentPlayer - 1].turnTaken) {
            int move = die.roll();
            //Move the player the rolled amount
            players[currentPlayer - 1].movePlayer(move);
            //Do whatever is on the landed field
            players[currentPlayer - 1].chooseAction();
            //Next turn
            nextTurn(currentPlayer);
        }
    }


    //Serverproof recursive nextTurn function
    void nextTurn(int curPlayer) {
        //If there are no next player to go to, then go to beginning of array of players
        if(players[curPlayer].hasPlayer) {
            currentPlayer++;
            players[currentPlayer - 1].setPlayersTurn();
            //If end of array has been reached, then restart
        } else if(curPlayer > 6){
            currentPlayer = 1;
            players[currentPlayer - 1].setPlayersTurn();
        } else {
            //If the end hasn't been reached, to make sure that if player 3 leaves, but player 4 and 5 are still playing
            //it should keep looking for players all the way through the loop, but still only pick up actual players
            nextTurn(curPlayer+1);
        }

    }

    Sprite drawPlayer(int curPlayer) {
        Sprite playerSpr;
            if(players[curPlayer].hasPlayer) {
                playerSpr = players[curPlayer].display();
            }
        return playerSpr;
    }

};
