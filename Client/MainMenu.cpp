#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Button.h"


using namespace std;
using namespace sf;

class MainMenu{
public:
    RenderWindow window;

    int getPlayerNum(){
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
    int start(){
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
};