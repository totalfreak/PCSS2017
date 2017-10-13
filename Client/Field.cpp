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
        for(int i = 0; i < numberOfFields; i++){
            Vector2f tempPos;
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
                fieldListRef.createField(i, "regular", regularFieldSizeX, tempPos);
            }
        }
    }

    /**
     * @param windowRef RenderWindow
     */
    void display(RenderWindow& windowRef, Fields& fieldListRef, int numberOfFields) {
        field *temp;
        temp = head;
        while(temp != nullptr) {
            RectangleShape rectangle;
            if(temp->type == "corner") {
                rectangle.setSize(temp->size);
                rectangle.setFillColor(Color::Red);
                rectangle.setOutlineColor(Color::Red);
                rectangle.setOutlineThickness(9);
                rectangle.setPosition(temp->position);
            }
            windowRef.draw(rectangle);

            temp = temp->next;
        }

    }

    Fields() {
        head = nullptr;
        tail = nullptr;
    }

};