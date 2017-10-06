#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;



class Dice {

    int rolled[2];


public:

    Texture chooseDiceTex(int* whatIsRolled);

    Texture diceTexes[2];

    Sprite diceSprites[2];

    //Dice textures
    Texture dice1, dice2, dice3, dice4, dice5, dice6;

    Dice() {
        if(!dice1.loadFromFile("Client/Sprites/spr_dice1.png") || !dice2.loadFromFile("Client/Sprites/spr_dice2.png") || !dice3.loadFromFile("Client/Sprites/spr_dice3.png") || !dice4.loadFromFile("Client/Sprites/spr_dice4.png") || !dice5.loadFromFile("Client/Sprites/spr_dice5.png") || !dice6.loadFromFile("Client/Sprites/spr_dice6.png")) {
            cout << "Error loading sprites";
        }


    }
    int* roll(){
        srand (time(NULL));

        rolled[0] = rand()%6+1;
        rolled[1] = rand()%6+1;
        return rolled;
    };


};
