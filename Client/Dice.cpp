#include <iostream>

using namespace std;

class Dice {

    int rolled[2];

public:
    int* roll(){
        srand (time(NULL));

        rolled[0] = rand()%6+1;
        rolled[1] = rand()%6+1;
        return rolled;
    };
};