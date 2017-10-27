
#include "Lobby.h"

Text Lobby::showTitle() {
    Text text;
    text.setFont(font);
    text.setString("Lobby");
    text.setCharacterSize(45);
    text.setFillColor(Color::Red);
    text.setPosition(350, 40);
    return text;

}

Text Lobby::showPlayerName(String pName, int yPos) {
    Text text;
    text.setFont(font);
    text.setString(pName);
    text.setCharacterSize(30);
    text.setFillColor(Color(155, 89, 182));
    text.setPosition(130, yPos);
    return text;
}

void Lobby::playMusic(){
    if (!music.openFromFile("Client/Audio/lobbymusic.wav")) {
        // error
    }
    music.setLoop(true);
    music.setVolume(50);
    music.play();
}

Sprite Lobby::spritesShow(Sprite sprite, int yPos) {
    sprite.setPosition(90, yPos);
    return sprite;
}

int Lobby::start() {
    playMusic();
    int numberOfButtons = 1;
    Button buttons[1];
    // Create one button to continue to game
    buttons[0].create(550.0f, 500.0f, "continue");
    window.create(sf::VideoMode(800, 600), "Lobby");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseMoved: {
                    Vector2i mousePos = Mouse::getPosition(window);
                    Vector2f mousePosF(static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ));

                    Sprite button;
                    for (int i = 0; i < numberOfButtons; i++) {
                        button = buttons[i].getSprite();

                        //If mouse is over button, change texture to 1 (highlighted button)
                        if (button.getGlobalBounds().contains(mousePosF)) {
                            buttons[i].setTex(1);
                        } else {
                            //else, change to default texture
                            buttons[i].setTex(0);
                        }
                    }
                }
                    break;
                case Event::MouseButtonPressed: {
                    Vector2i mousePos = Mouse::getPosition(window);
                    Vector2f mousePosF(static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ));
                    Sprite button;
                    for (int i = 0; i < numberOfButtons; i++) {
                        button = buttons[i].getSprite();
                        // if button is pressed, change texture to 2 (pushed down)
                        if (button.getGlobalBounds().contains(mousePosF)) {
                            buttons[i].setTex(2);
                        }
                    }
                }
                    break;
                case Event::MouseButtonReleased: {
                    Vector2i mousePos = Mouse::getPosition(window);
                    Vector2f mousePosF(static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ));
                    Sprite button;
                    for (int i = 0; i < numberOfButtons; i++) {

                        button = buttons[i].getSprite();
                        // if mouse is released, change button texture to 1 (highlighted)
                        if (button.getGlobalBounds().contains(mousePosF)) {
                            buttons[i].setTex(1);
                            music.stop();
                            window.close();
                            return 1;
                        }
                    }
                }
                    break;
                default:
                    break;
            }
        }
        window.clear(Color::White);
        for (int i = 0; i < numberOfButtons; i++) {
            window.draw(buttons[i].getSprite());
        }
        window.draw(showPlayerName("Jeffery", 120));
        window.draw(showPlayerName("Horse Penis", 160));
        window.draw(showPlayerName("Mr. Dick Jail", 200));
        window.draw(spritesShow(tempSprite, 120));
        window.draw(spritesShow(tempSprite, 160));
        window.draw(spritesShow(tempSprite, 200));


        window.draw(showTitle());
        window.display();
    }

    return 0;

}

Lobby::Lobby() {

    if (!font.loadFromFile("Fonts/TheLightFont.ttf")) {
        perror("Font couldn't load");
    }

    if(!texBrickFrog.loadFromFile("Client/Sprites/spr_frogTemp.png")) {
        cout << "Error loading player brick textures";
    }
    tempSprite.setTexture(texBrickFrog);
}
