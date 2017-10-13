//
// Created by rasmus on 10/13/17.
//

#ifndef PCSS2017_FIELDS_H
#define PCSS2017_FIELDS_H

#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace std;
using namespace sf;

const Vector2f startPos = Vector2f(518.f, 518.f);
const Vector2f cornerFieldSize = Vector2f(72.f, 72.f);
const Vector2f regularFieldSizeX = Vector2f(26.f, 72.f);
const Vector2f regularFieldSizeY = Vector2f(72.f, 26.f);


struct field {
    int number;
    Vector2f position;
    Vector2f size;
    //Player* playersOnField = new Player[6]; //todo: Fixes #12 : We need to separate headers and classes in order to be able to include them in different files properly
    string type; //regular - corner
    field *next;
};

class Fields {

private:
    field *head, *tail;
public:
    void createField(int n, string s, Vector2f size, Vector2f pos);
    void setupFields(Fields& fieldListRef, int numberOfFields);

    void display(RenderWindow& windowRef, Fields& fieldListRef, int numberOfFields);
    Fields();

};

#endif //PCSS2017_FIELDS_H
