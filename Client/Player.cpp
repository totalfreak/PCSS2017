#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player {
    string playerName;
    int position; //between 0 and 39
    int points;
    bool isPlayersTurn;
    Texture playerTexture;
    Sprite playerSprite;

public:
    Player(string name, Texture tex){
        playerName = name;
        playerTexture = tex;
        playerSprite.setTexture(playerTexture);
        position = 0;
        points = 0;
        isPlayersTurn = false;
    }
    void setPlayersTurn(bool x)
    {
        isPlayersTurn = x;
        chooseAction();
    }
    int getPosition(){
        return position;
    }
    Sprite display(){
        playerSprite.setPosition(600, 0);
        return playerSprite;
    }
private:
    void chooseAction(){
        if(isPlayersTurn)
        {
            cout << this->playerName << "'s turn began" << endl;
            // roll dice
            endTurn();
        }
    }
    void movePlayer(int* diceRoll){
        position += diceRoll[0] + diceRoll[1];
    }
    void endTurn(){
        isPlayersTurn = false;
        cout << this->playerName << "'s turn ended" << endl;
        //inform server
    }
};



