#include <iostream>
#include <SFML/Graphics.hpp>

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
    void createField(int n, string s, Vector2f size, Vector2f pos)
    {
        field *temp = new field;
        temp->number = n;
        temp->type = s;
        temp->size = size;
        temp->position = pos;
        temp->next = nullptr;

        if(head == nullptr) {
            head = temp;
            tail = temp;

        } else {
            tail->next = temp;
            tail = temp;
        }

    }

    void setupFields(Fields& fieldListRef, int numberOfFields){
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

    /**
     * @param windowRef RenderWindow
     */
    void display(RenderWindow& windowRef, Fields& fieldListRef, int numberOfFields) {
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

    Fields() {
        head = nullptr;
        tail = nullptr;
    }

};