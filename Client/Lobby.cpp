
#include "Lobby.h"

Text Lobby::showTitle() {
    Text text;
    text.setFont(font);
    text.setString("Lobby");
    text.setCharacterSize(35);
    text.setFillColor(Color::Black);
    text.setPosition(350, 15);
    text.setOutlineThickness(1);
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

Text Lobby::showPlayers(){
    Text text;
    text.setFont(font);
    text.setString("Players waiting...");
    text.setCharacterSize(20);
    text.setFillColor(Color::Black);
    text.setPosition(48, 70);
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


Sprite Lobby::spritesShow(Sprite sprite, int yPos){
    sprite.setPosition(73, yPos);
    return sprite;
}

Texture texCharA, texCharB, texCharC, texCharD, texCharE,texCharF;
int selected = -1;

int Lobby::start() {
    playMusic();
    int numberOfButtons = 8;
    Button buttons[8];
    // Create one button to continue to game
    buttons[0].create(580.0f, 530.0f, "continue");
    buttons[7].create(380.0f, 530.0f, "leave");

    for(int i = 0; i<numberOfButtons-2; i++){
        string path = "characters/";
        path+=std::to_string(i);
        buttons[i+1].create(400+100*(i%2),100+100*(i/2),path);
    }
    window.create(sf::VideoMode(800, 600), "Lobby");


    while (window.isOpen()) {

        game->network();
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
                            //Else, change to default texture
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
                        //If button is pressed, change texture to 2 (pushed down)
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
                        //If mouse is released, change button texture to 1 (highlighted)
                        if (button.getGlobalBounds().contains(mousePosF)) {
                            buttons[i].setTex(2);
                            if(i==0){
                                //continue button
                                if(selected!=-1) {
                                    window.close();
                                    music.stop();
                                    std::cout << "Returned texture from button " << selected << endl;
                                    return selected-1;
                                }
                            } else if(i==7){
                                window.close();
                                music.stop();
                                return -1;
                            } else {
                                selected = i;
                                game->client1->changePic(selected-1);
                                std::cout << "Set selected to " << i << endl;
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
        window.draw(bgSprite);
        for (int i = 0; i < numberOfButtons; i++) {
            window.draw(buttons[i].getSprite());
        }
        window.draw(rectangle);

        for(int i = 0 ; i < 6 ; i++){   //for each player spot(6) in the game
            if(!game->players[i].hasPlayer){continue;} // if there is no player there is nothing
            window.draw(showPlayerName(game->players[i].playerName, 120 + i*40));
            window.draw(spritesShow(game->players[i].playerBrickSpr, 120 + i*40));
        }

        window.draw(showPlayers());
        window.draw(showTitle());

        Text text;
        text.setFont(font);
        text.setString("Choose a character");
        text.setCharacterSize(20);
        text.setFillColor(Color::Black);
        text.setPosition(400, 70);
        window.draw(text);

        window.display();
    }

    return 0;
}

Lobby::Lobby() {
    game = nullptr;

    if (!font.loadFromFile("Fonts/TheLightFont.ttf")) {
        perror("Font couldn't load");
    }

    if(!texBrickFrog.loadFromFile("Client/Sprites/spr_frogTemp.png")) {
        cout << "Error loading player brick textures";
    }
    tempSprite.setTexture(texBrickFrog);

    if(!texBg.loadFromFile("Client/Sprites/lobbybg.png")) {
        cout << "Error loading player brick textures";
    }
    bgSprite.setTexture(texBg);

    rectangle = RectangleShape(sf::Vector2f(120, 50));
    rectangle.setOutlineColor(sf::Color(117, 117, 117));
    rectangle.setSize(sf::Vector2f(300, 400));
    rectangle.setPosition(50, 100);
    rectangle.setFillColor(sf::Color(255, 255, 255, 100));
    rectangle.setOutlineThickness(1);
}

Lobby::Lobby(GameManager * creator) {

    //This version can make changes to the gamemanager that created it

    game = creator;
    if (!font.loadFromFile("Fonts/TheLightFont.ttf")) {
        perror("Font couldn't load");
    }

    if(!texBrickFrog.loadFromFile("Client/Sprites/spr_frogTemp.png")) {
        cout << "Error loading player brick textures";
    }
    tempSprite.setTexture(texBrickFrog);

    if(!texBg.loadFromFile("Client/Sprites/lobbybg.png")) {
        cout << "Error loading player brick textures";
    }
    bgSprite.setTexture(texBg);


    rectangle = RectangleShape(sf::Vector2f(120, 50));
    rectangle.setOutlineColor(sf::Color(117, 117, 117));
    rectangle.setSize(sf::Vector2f(300, 400));
    rectangle.setPosition(50, 100);
    rectangle.setFillColor(sf::Color(255, 255, 255, 100));
    rectangle.setOutlineThickness(1);
}