#include <iostream>

using namespace std;

struct field {
    int number;
    string type; //regular - corner
    field *next;
};

class Fields {
private:
    field *head, *tail;

public:
    void createField(int n, string s)
    {
        field *temp = new field;
        temp->number = n;
        temp->type = s;
        temp->next = nullptr;

        if(head == nullptr) {
            head = temp;
            tail = temp;

        } else {
            tail->next = temp;
            tail = temp;
        }

    }

    void display() {
        field *temp;
        temp = head;
        while(temp != nullptr) {
            cout << temp->number << " - " << temp->type << "\n";
            temp = temp->next;
        }
    }

    Fields() {
        head = nullptr;
        tail = nullptr;
    }

};