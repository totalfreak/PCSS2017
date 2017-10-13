

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class Lobby {

public:
    sf::Font font;
    Lobby() {

        if (!font.loadFromFile("Fonts/TheLightFont.ttf")) {
            perror("Font couldn't load");
        }
    }

        Text showTitle(){
        Text text;
        text.setFont(font);
        text.setString("Lobby");
        text.setCharacterSize(40);
        text.setColor(Color::Red);
        text.setPosition(650, 50);
        return text;
    }
};