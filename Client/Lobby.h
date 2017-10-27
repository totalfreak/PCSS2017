//
// Created by simone on 10/20/17.
//

#ifndef PCSS2017_LOBBY_H
#define PCSS2017_LOBBY_H

#include <iostream>
#include "SFML/Window.hpp"
#include <SFML/Graphics.hpp>
#include "Client/Button.h"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;


class Lobby {

public:
    sf::Font font;
    Sprite sprites[6];
    Texture texBrickFrog;
    Sprite tempSprite;
    Lobby();

    void playMusic();
    Text showTitle();
    Text showPlayerName(String pName, int yPos);
    Sprite spritesShow(Sprite sprite, int yPos);

    RenderWindow window;

    int start();
};



#endif //PCSS2017_LOBBY_H


