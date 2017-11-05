#include "MainMenu.h"

int MainMenu::getPlayerNum() {
    int numberOfButtons = 6;
    Button buttons[6];
    for(int i = 0; i<numberOfButtons; i++){
        buttons[i].create(100.0f*(i+1),200.0f,to_string(i+1));
    }
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch ( event.type )
            {
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseMoved:
                {
                    Vector2i mousePos = Mouse::getPosition( window );
                    Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                    Sprite button;
                    for(int i = 0; i<numberOfButtons; i++) {
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
                case Event::MouseButtonPressed:
                {
                    Vector2i mousePos = Mouse::getPosition( window );
                    Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    Sprite button;
                    for(int i = 0; i<numberOfButtons; i++) {

                        button = buttons[i].getSprite();
                        // if button is pressed, change texture to 2 (pushed down)
                        if (button.getGlobalBounds().contains(mousePosF)) {
                            buttons[i].setTex(2);
                        }
                    }
                }
                    break;
                case Event::MouseButtonReleased:
                {
                    Vector2i mousePos = Mouse::getPosition( window );
                    Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    Sprite button;
                    for(int i = 0; i<numberOfButtons; i++) {

                        button = buttons[i].getSprite();
                        // if mouse is released, change button texture to 1 (highlighted)
                        if (button.getGlobalBounds().contains(mousePosF)) {
                            buttons[i].setTex(1);
                            window.close();
                            return(i+1);
                        }
                    }
                }
                    break;
                default:
                    break;
            }
        }
        window.clear(Color::White);
        for(int i = 0; i<numberOfButtons; i++) {
            window.draw(buttons[i].getSprite());
        }
        window.display();
    }
    return 0;
}

int MainMenu::start() {
    int numberOfButtons = 3;
    Button buttons[3];
    // Create three buttons: Host game, join game, exit game
    buttons[0].create(200.0f,100.0f,"host");
    buttons[1].create(200.0f,250.0f,"join");
    buttons[2].create(200.0f,400.0f,"exit");
    window.create(sf::VideoMode(800, 600), "Menu");

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch ( event.type )
            {
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseMoved:
                {
                    Vector2i mousePos = Mouse::getPosition( window );
                    Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                    Sprite button;
                    for(int i = 0; i<numberOfButtons; i++) {
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
                case Event::MouseButtonPressed:
                {
                    Vector2i mousePos = Mouse::getPosition( window );
                    Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    Sprite button;
                    for(int i = 0; i<numberOfButtons; i++) {

                        button = buttons[i].getSprite();
                        // if button is pressed, change texture to 2 (pushed down)
                        if (button.getGlobalBounds().contains(mousePosF)) {
                            buttons[i].setTex(2);
                        }
                    }
                }
                    break;
                case Event::MouseButtonReleased:
                {
                    Vector2i mousePos = Mouse::getPosition( window );
                    Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    Sprite button;
                    for(int i = 0; i<numberOfButtons; i++) {

                        button = buttons[i].getSprite();
                        // if mouse is released, change button texture to 1 (highlighted)
                        if (button.getGlobalBounds().contains(mousePosF)) {
                            buttons[i].setTex(1);
                            switch (i)
                            {
                                case 0: // Host Server
                                    return 1;
                                    break;
                                case 1: // Join Server
                                    return 2;
                                    break;
                                case 2: // Exit Game
                                    window.close();
                                    return 0;
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
        for(int i = 0; i<numberOfButtons; i++) {
            window.draw(buttons[i].getSprite());
        }
        window.display();
    }
    return 0;
}


string MainMenu::getName() {
    sf::Font font;
    if (!font.loadFromFile("Fonts/TheLightFont.ttf")) {
        perror("Font couldn't load");
    }
    string address;
    sf::Text text;
    sf:Text title;

    title.setFont(font);
    title.setCharacterSize(40);
    title.setString("what do you wanna be called?");
    title.setFillColor(Color::Black);
    title.setPosition(200, 100);

    text.setString("");
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(Color::Black);
    text.setPosition(320, 200);
    int numberOfButtons = 1;
    Button buttons[1];
    // Create three buttons: Host game, join game, exit game
    buttons[0].create(300.0f,500.0f,"continue");
    window.create(sf::VideoMode(800, 600), "Menu");

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch ( event.type )
            {
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseMoved:
                {
                    Vector2i mousePos = Mouse::getPosition( window );
                    Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                    Sprite button;
                    for(int i = 0; i<numberOfButtons; i++) {
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
                case Event::MouseButtonPressed:
                {
                    Vector2i mousePos = Mouse::getPosition( window );
                    Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    Sprite button;
                    for(int i = 0; i<numberOfButtons; i++) {

                        button = buttons[i].getSprite();
                        // if button is pressed, change texture to 2 (pushed down)
                        if (button.getGlobalBounds().contains(mousePosF)) {
                            buttons[i].setTex(2);
                        }
                    }
                }
                    break;
                case Event::MouseButtonReleased:
                {
                    Vector2i mousePos = Mouse::getPosition( window );
                    Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    Sprite button;
                    for(int i = 0; i<numberOfButtons; i++) {

                        button = buttons[i].getSprite();
                        // if mouse is released, change button texture to 1 (highlighted)
                        if (button.getGlobalBounds().contains(mousePosF)) {
                            buttons[i].setTex(1);
                            window.close();
                            switch (i) {
                                case 0: // Host Server
                                    return address;
                                    break;
                            }
                        }
                    }
                }
                    break;
                case Event::TextEntered:
                    if (event.text.unicode < 128) {
                        if(event.text.unicode == '\b'){
                            address.pop_back();
                            cout << address;
                            text.setString(address);
                        } else if (event.text.unicode < 128) {
                            address.push_back((char)event.text.unicode);
                            text.setString(address);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        window.clear(Color::White);

        for(int i = 0; i<numberOfButtons; i++) {
            window.draw(buttons[i].getSprite());
        }
        window.draw(title);
        window.draw(text);
        window.display();
    }
    return address;
}

string MainMenu::ipAddressGet() {
    sf::Font font;
    if (!font.loadFromFile("Fonts/TheLightFont.ttf")) {
        perror("Font couldn't load");
    }
    string address;
    sf::Text text;
    sf:Text title;

    title.setFont(font);
    title.setCharacterSize(40);
    title.setString("Enter IP address of host");
    title.setFillColor(Color::Black);
    title.setPosition(200, 100);

    text.setString("");
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(Color::Black);
    text.setPosition(320, 200);
    int numberOfButtons = 1;
    Button buttons[1];
    // Create three buttons: Host game, join game, exit game
    buttons[0].create(300.0f,500.0f,"continue");
    window.create(sf::VideoMode(800, 600), "Menu");

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch ( event.type )
            {
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseMoved:
                {
                    Vector2i mousePos = Mouse::getPosition( window );
                    Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

                    Sprite button;
                    for(int i = 0; i<numberOfButtons; i++) {
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
                case Event::MouseButtonPressed:
                {
                    Vector2i mousePos = Mouse::getPosition( window );
                    Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    Sprite button;
                    for(int i = 0; i<numberOfButtons; i++) {

                        button = buttons[i].getSprite();
                        // if button is pressed, change texture to 2 (pushed down)
                        if (button.getGlobalBounds().contains(mousePosF)) {
                            buttons[i].setTex(2);
                        }
                    }
                }
                    break;
                case Event::MouseButtonReleased:
                {
                    Vector2i mousePos = Mouse::getPosition( window );
                    Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    Sprite button;
                    for(int i = 0; i<numberOfButtons; i++) {

                        button = buttons[i].getSprite();
                        // if mouse is released, change button texture to 1 (highlighted)
                        if (button.getGlobalBounds().contains(mousePosF)) {
                            buttons[i].setTex(1);
                            window.close();
                            switch (i) {
                                case 0: // Host Server
                                    return address;
                                    break;
                            }
                        }
                    }
                }
                    break;
                case Event::TextEntered:
                    if (event.text.unicode < 128) {
                        if(event.text.unicode == '\b'){
                            address.pop_back();
                            cout << address;
                            text.setString(address);
                        } else if (event.text.unicode < 128) {
                            address.push_back((char)event.text.unicode);
                            text.setString(address);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        window.clear(Color::White);

        for(int i = 0; i<numberOfButtons; i++) {
            window.draw(buttons[i].getSprite());
        }
        window.draw(title);
        window.draw(text);
        window.display();
    }
    return address;
}
