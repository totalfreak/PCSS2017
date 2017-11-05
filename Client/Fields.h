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




struct field {
public:

    int number;
    Vector2f position;
    Vector2f size;
    int * playersOnField = new int[6];
    string type; //regular - corner
    field *next;
    bool isActive;
};

class Fields {


private:
    field *head, *tail;

public:
    Vector2f startPos;
    Vector2f cornerFieldSize ;
    Vector2f regularFieldSizeX;
    Vector2f regularFieldSizeY;


    void createField(int n, string s, Vector2f size, Vector2f pos, bool isActive);
    void setupFields(int numberOfFields);

    void display(RenderWindow &windowRef, Fields &fieldListRef);
    void displaySingle(RenderWindow &windowRef, field * displayField);
    Fields();

    field *getHead();
};

#endif //PCSS2017_FIELDS_H
