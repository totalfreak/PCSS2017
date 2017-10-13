#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Button.cpp"


using namespace std;
using namespace sf;

class MainMenu{
public:

    int start(){
        Button buttons[3];
        // Create three buttons: Host game, join game, exit game
        buttons[0].create(200.0f,100.0f,"host");
        buttons[1].create(200.0f,250.0f,"join");
        buttons[2].create(200.0f,400.0f,"exit");

        RenderWindow window(VideoMode(800, 600), "Menu");

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
                        for(int i = 0; i<3; i++) {
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
                        for(int i = 0; i<3; i++) {

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
                        for(int i = 0; i<3; i++) {

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
            for(int i = 0; i<3; i++) {
                window.draw(buttons[i].getSprite());
            }
            window.display();
        }
        return 0;
    }
};