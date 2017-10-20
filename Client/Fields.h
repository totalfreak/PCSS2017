//
// Created by rasmus on 10/13/17.
//

#ifndef PCSS2017_FIELDS_H
#define PCSS2017_FIELDS_H

#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "constants.h"

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
    int * playersOnField = new int[6];
    string type; //regular - corner
    field *next;
};

class Fields {

private:
    field *head, *tail;
public:
    void createField(int n, string s, Vector2f size, Vector2f pos);
    void setupFields(Fields& fieldListRef, int numberOfFields);

    void display(RenderWindow &windowRef, Fields &fieldListRef);
    Fields();

    field *getHead();
};

#endif //PCSS2017_FIELDS_H
