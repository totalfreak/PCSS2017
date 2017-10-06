#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player {
    String playerName;
    int position;
    int points;
    bool isPlayersTurn;

public:
    Player(String name){
        playerName = name;
        position = 0;
        points = 0;
        isPlayersTurn = false;
    }
    void setPlayersTurn(bool x)
    {
        isPlayersTurn = x;
    }
    void chooseAction(){
        if(isPlayersTurn)
        {
            cout << playerName+"'s turn began" << endl;
            // roll dice
            endTurn();
        }
    }
    void movePlayer(int* diceRoll){
        position += diceRoll[0] + diceRoll[1];
    }
    void endTurn(){
        isPlayersTurn = false;
        cout << playerName+"'s turn ended" << endl;
        //inform server
    }
};



