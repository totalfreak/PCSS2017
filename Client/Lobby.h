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
#include "GameManager.h"

using namespace std;
using namespace sf;

class GameManager;

class Lobby {



public:

    Lobby();

    Lobby(GameManager *creator); //use this one it can make changes to the gamemanger that created it



    GameManager * game;
    sf::Font font;
    sf::Music music;
    Sprite sprites[6];
    Texture texBrickFrog;
    Texture texBg;
    Sprite tempSprite;
    Sprite bgSprite;

    Text showPlayers();
    void playMusic();
    Text showTitle();
    Text showPlayerName(String pName, int yPos);
    Sprite spritesShow(Sprite sprite, int yPos);

    RectangleShape rectangle;


    RenderWindow window;

    int start();
};



#endif //PCSS2017_LOBBY_H


