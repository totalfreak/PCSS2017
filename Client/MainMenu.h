//
// Created by Marcus Alexander Skytt on 13/10/2017.
//

#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Button.h"


#ifndef PCSS2017_MAINMENU_H
#define PCSS2017_MAINMENU_H

using namespace std;
using namespace sf;
class MainMenu {

    public:
        RenderWindow window;


        int getPlayerNum();
        int start();

        string ipAddressGet();

};
#endif //PCSS2017_MAINMENU_H

