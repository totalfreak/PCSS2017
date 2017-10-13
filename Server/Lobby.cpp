//
// Created by simone on 10/13/17.
//

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class Lobby {

    Lobby() {
        sf::Font font;
        if (!font.loadFromFile("../Fonts/TheLightFont.ttf")) {
            perror("Font couldn't load");
        }}
};