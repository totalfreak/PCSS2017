#include "Button.h"

Button::Button() {
}

void Button::create(float x, float y, string name) {
    this->name = name;
    buttonx = x;
    buttony = y;
    if(!textures[0].loadFromFile("Client/Sprites/buttons/"+name+"/0.png") || !textures[1].loadFromFile("Client/Sprites/buttons/"+name+"/1.png") || !textures[2].loadFromFile("Client/Sprites/buttons/"+name+"/2.png")) {
        cout << "Error loading button textures";
    }
    button.setPosition(buttonx,buttony);
    button.setTexture( textures[0] );

}

Sprite Button::getSprite() {
    this->button.setPosition(buttonx, buttony);
    return this->button;
}
Texture Button::getTex(){
    return this->textures[0];
}
void Button::setTex(int n) {
    this->button.setTexture(textures[n]);
}
