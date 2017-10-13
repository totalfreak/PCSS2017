#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Button {
public:
    Texture textures[3];
    Sprite button;
    float buttonx;
    float buttony;
    string name;
    Button(){
    }
    void create(float x, float y, string name){
        this->name = name;
        buttonx = x;
        buttony = y;
        if(!textures[0].loadFromFile("Client/Sprites/buttons/"+name+"/0.png") || !textures[1].loadFromFile("Client/Sprites/buttons/"+name+"/1.png") || !textures[2].loadFromFile("Client/Sprites/buttons/"+name+"/2.png")) {
            cout << "Error loading button textures";
        }
        button.setPosition(buttonx,buttony);
        button.setTexture( textures[0] );

    }
    Sprite getSprite(){
        this->button.setPosition(buttonx, buttony);
        return this->button;
    }
    void setTex(int n){
        this->button.setTexture(textures[n]);
    }

};
