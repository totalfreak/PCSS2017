//
// Created by simone on 10/20/17.
//

#ifndef PCSS2017_LOBBY_H
#define PCSS2017_LOBBY_H

#include <iostream>
#include "SFML/Window.hpp"
#include <SFML/Graphics.hpp>
#include "Client/Button.h"

using namespace std;
using namespace sf;


class Lobby {

public:
    sf::Font font;
    Lobby();

    Text showTitle();

    RenderWindow window;

    int start();
};



#endif //PCSS2017_LOBBY_H

