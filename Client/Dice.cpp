#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;



class Dice {
public:

    int rolled[2];
    Texture diceTexes[2];
    Sprite diceSprites[2];
    //Dice textures
    Texture dice1, dice2, dice3, dice4, dice5, dice6;
    //Constructor
    Dice() {
        if(!dice1.loadFromFile("Client/Sprites/spr_dice1.png") || !dice2.loadFromFile("Client/Sprites/spr_dice2.png") || !dice3.loadFromFile("Client/Sprites/spr_dice3.png") || !dice4.loadFromFile("Client/Sprites/spr_dice4.png") || !dice5.loadFromFile("Client/Sprites/spr_dice5.png") || !dice6.loadFromFile("Client/Sprites/spr_dice6.png")) {
            cout << "Error loading sprites";
        }
    }
    int roll(){


        //Doing two dice rolls
        rolled[0] = rand()%6+1;
        rolled[1] = rand()%6+1;
        //Saving the rolled textures
        *diceTexes = chooseDiceTex(rolled);
        diceSprites[0].setTexture(diceTexes[0]);
        diceSprites[1].setTexture(diceTexes[1]);
        return rolled[0]+rolled[1];
    };

    Texture chooseDiceTex(int* whatIsRolled) {
        //Switch case, showing the right dice texture, dependent on what was rolled

        Texture texes[2];
        switch (whatIsRolled[0]) {
            case 1:
                texes[0] = dice1;
                break;
            case 2:
                texes[0] = dice2;
                break;
            case 3:
                texes[0] = dice3;
                break;
            case 4:
                texes[0] = dice4;
                break;
            case 5:
                texes[0] = dice5;
                break;
            case 6:
                texes[0] = dice6;
                break;
        }
        switch (whatIsRolled[1]) {
            case 1:
                texes[1] = dice1;
                break;
            case 2:
                texes[1] = dice2;
                break;
            case 3:
                texes[1] = dice3;
                break;
            case 4:
                texes[1] = dice4;
                break;
            case 5:
                texes[1] = dice5;
                break;
            case 6:
                texes[1] = dice6;
                break;
        }
        diceTexes[0] = texes[0];
        diceTexes[1] = texes[1];
        return *texes;
    }


};
