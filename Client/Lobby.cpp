
#include "Lobby.h"

Text Lobby::showTitle() {
    Text text;
    text.setFont(font);
    text.setString("Lobby");
    text.setCharacterSize(40);
    text.setColor(Color::Red);
    text.setPosition(370, 50);
    return text;

}

int Lobby::start() {
    int numberOfButtons = 1;
    Button buttons[1];
    // Create one button to continue to game
    buttons[0].create(200.0f, 100.0f, "continue");
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
                            switch (i) {

                                case 1: // Join Server
                                    return 2;
                                    break;

                            }
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
        window.display();
    }
    return 0;
}

Lobby::Lobby() {

    if (!font.loadFromFile("Fonts/TheLightFont.ttf")) {
        perror("Font couldn't load");
    }
}
