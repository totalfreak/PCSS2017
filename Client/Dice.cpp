#include <iostream>

using namespace std;

class Dice {
public:
    int roll(){
        srand (time(NULL));
        return rand()%6+1;
    };
};