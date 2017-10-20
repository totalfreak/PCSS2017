
#include "Player.h"


Player::Player(string name, Texture picTex, Texture brickTex, int ID, field * pos) {
    playerName = name;
    playerTexture = picTex;
    playerSprite.setTexture(playerTexture);
    playerBrickTex = brickTex;
    playerBrickSpr.setTexture(playerBrickTex);
    position = Vector2f(300,300);
    points = 0;
    isPlayersTurn = false;
    turnTaken = false;
    hasPlayer = true;
    speed = DEFAULTSPEED;
    myID = ID;
    moveTo(pos);

}

void Player::setPlayersTurn() {
    isPlayersTurn = true;
    cout << endl << this->playerName << "'s turn began" << endl;
}

Vector2f Player::getPosition() {
    return position;
}

void Player::setPosition(int tempX, int tempY) {
    this->position = Vector2f(tempX, tempY);
}

void Player::physics() {
    if(!hasPlayer){return;}
    if( tile == nullptr){return;}

    int nrOnField = 0;
    int myNr = 0;
    int playerID;
    for(int i = 0; i < 6 ; i ++){
        playerID = *tile->playersOnField + i;
        if( playerID != FIELD_EMPTY){
            nrOnField++;
            if(playerID == myID){
                myNr = nrOnField;
            }
        }
    }
    nrOnField++; // we increment to avoid having people at the ends of the tile
    Vector2f goal;
    goal = Vector2f(tile->position.x + tile->size.x/2 , tile->position.y + tile->size.y  * 0.1 + 0.8 * (myNr/nrOnField) * tile->size.y );

    float dist = distance(goal, getPosition());

    double timeSinceLastMove = getMoveTime();

    currentSpeed = (speed + dist  * distanceFactor);

    float moveSpeed = (float)(timeSinceLastMove * currentSpeed );



    if(dist  < moveSpeed){
        setPosition(goal);

        return;
    }

    Vector2f moveDirection = Vector2f(goal - getPosition());
    normalize(&moveDirection);

    moveDirection *= moveSpeed;


    setPosition( getPosition() + moveDirection);
}

double Player::getMoveTime(){// gets time in microseconds since last move
    tempTime = high_resolution_clock::now();
    duration<double> timeSince =  tempTime - LastMove;

    LastMove = tempTime;
    return timeSince.count();
}

float Player::distance(Vector2f one, Vector2f two) {
    float dist = pow(one.x - two.x, 2) + pow(one.y - two.y , 2); //phythaoran theorem
    return sqrt(dist); // now we have the length of the hypotenus
}

void Player::normalize(Vector2f * in) {
    float length = pow(in->x,2) + pow(in->y,2); //phythaoran theorem
    length = sqrt(length); // now we have the length of the hypotenuse
    *in *= 1/length;
}

Sprite Player::display() {
    playerBrickSpr.setTexture(playerBrickTex);
    this->playerBrickSpr.setPosition(getPosition().x, getPosition().y);
    float scaleFactor = (currentSpeed+movescaleAdjust)/(DEFAULTSPEED+movescaleAdjust) ;
    playerBrickSpr.setScale(scaleFactor,scaleFactor);
    return this->playerBrickSpr;
}

void Player::movePlayer(int rolled) {

    cout << endl <<  "Player " <<  playerName << " just moved " << rolled << " spaces";
    //TODO Make fit into whatever model we make the doubly linked list of Fields be
    field * dest = tile;
    //iterate throught he field
    for(int i = 0 ; i < rolled ; i++){

        if(dest->next != nullptr) {
            dest = dest->next;
        }
    }
    moveTo(dest);
}

void Player::moveTo(field *dest) {
    if(dest != nullptr) {
        //delete us on the field we are on
        if (tile != nullptr) {
        for (int i = 0; i < 6; i++) {
            if (*(tile->playersOnField + i) == myID) {
                *(tile->playersOnField +
                  i) = FIELD_EMPTY; // we use -1 to denote that no players are on the this index of the array
            }
        }
    }
        // then add us at the destination
        tile = dest;
        for(int i = 0 ; i < 6 ; i++) {
            if ( *(tile->playersOnField + i) == FIELD_EMPTY) {
                *(tile->playersOnField + i) = myID;
            }
        }

    }
}

void Player::endTurn() {
    isPlayersTurn = false;
    cout << endl << this->playerName << "'s turn ended" << endl;
    //inform the server
}

void Player::chooseAction() {
    if(isPlayersTurn)
    {

        //Do something related to what field you landed on here

        endTurn();
        //Inform the server
    }
}

void Player::setPosition(Vector2f pos) {
    this->position = pos;
}
