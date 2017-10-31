//
// Created by Nicolai Lorits on 13/10/17.
//

#ifndef PCSS2017_BUTTON_H
#define PCSS2017_BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Button {
public:
    Texture textures[3];
    Sprite button;
    float buttonx;
    float buttony;
    string name;
    Button();
    void create(float x, float y, string name);
    Sprite getSprite();
    Texture getTex();
    void setTex(int n);

};

#endif //PCSS2017_BUTTON_H
