//
// Created by rasmus on 10/13/17.
//

#include "Fields.h"


void Fields::createField(int n, string s, Vector2f size, Vector2f pos) {
    field *temp = new field;
    temp->number = n;
    temp->type = s;
    temp->size = size;
    temp->position = pos;
    temp->next = nullptr;

    for(int i = 0 ; i < 6 ; i++){//allow players to go to the field
        *(temp->playersOnField + i) = FIELD_EMPTY; // set all fields to -1
    }

    if(head == nullptr) {
        head = temp;
        tail = temp;

    } else {
        tail->next = temp;
        tail = temp;
    }

}

Fields::Fields() {
    head = nullptr;
    tail = nullptr;

}

field * Fields::getHead(){
    return head;
}

void Fields::display(RenderWindow &windowRef, Fields &fieldListRef, int numberOfFields) {
    field *temp;
    temp = head;
    Color color;
    while(temp != nullptr) {
        RectangleShape rectangle;
        rectangle.setSize(temp->size);
        rectangle.setPosition(temp->position);
        if(temp->type == "regular") {
            color = Color::Blue;
        } else {
            color = Color::Red;
        }
        rectangle.setFillColor(color);
        rectangle.setOutlineColor(color);
        rectangle.setOutlineThickness(9);


        windowRef.draw(rectangle);

        temp = temp->next;
    }

}


void Fields::setupFields(Fields &fieldListRef, int numberOfFields) {
    int k;
    for(int i = 0; i < numberOfFields; i++){
        k = i % 10;

        Vector2f tempPos;
        Vector2f tempSize;
        if(i == 0 || i == 10 || i == 20 || i == 30){
            switch(i){
                case 0:
                    tempPos = startPos;
                    break;
                case 10:
                    tempPos = Vector2f(10, startPos.y);
                    break;
                case 20:
                    tempPos = Vector2f(10,10);
                    break;
                case 30:
                    tempPos = Vector2f(startPos.x, 10);
                    break;
            }
            fieldListRef.createField(i, "corner", cornerFieldSize,tempPos);
        } else {
            if(i > 0 && i < 10 || i > 20 && i < 30){
                tempSize = regularFieldSizeX;
            } else {
                tempSize = regularFieldSizeY;
            }

            if(i > 0 && i < 10){
                tempPos = Vector2f(startPos.x - ((tempSize.x*k)*2)+k*6,startPos.y);
            } else if(i > 10 && i < 20){
                tempPos = Vector2f(10 , startPos.y-((tempSize.y*k)*2)+k*6);
            } else if(i > 20 && i < 30){
                tempPos = Vector2f(cornerFieldSize.x-15 + ((tempSize.x*k)*2)-k*6, 10);
            } else if(i > 30 && i < 40){
                tempPos = Vector2f(startPos.x, cornerFieldSize.y-15 +((tempSize.y*k)*2)-k*6);
            }

            fieldListRef.createField(i, "regular", tempSize, tempPos);
        }
    }
}

