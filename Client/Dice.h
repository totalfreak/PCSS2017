//
// Created by rasmus on 11/2/17.
//

#ifndef PCSS2017_DICE_H
#define PCSS2017_DICE_H


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
    Dice();
    int roll();;

    Texture chooseDiceTex(int* whatIsRolled);


};


#endif //PCSS2017_DICE_H
