
#include "Player.h"


Player::Player(string name, Texture picTex, Texture brickTex, int ID, field * pos) {
    if(name == ""){
        name = "no name";
    }
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
    tile = pos;
    moveTo(pos, myID);


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
    if(!hasPlayer || tile == nullptr){return;}

    int nrOnField = 0;
    int myNr = 0;
    int playerID;
    for(int i = 0; i < 6 ; i ++){
        playerID = *(tile->playersOnField + i);
        if( playerID != FIELD_EMPTY){
            nrOnField++;
            if(playerID == myID){

            myNr = nrOnField;
            }
        }
    }
    nrOnField++; // we increment to avoid having people at the ends of the tile
    Vector2f goal;
    goal = Vector2f(tile->position.x + tile->size.x/2 , tile->position.y + (0.1 + 0.8 * ((float)myNr/nrOnField) * tile->size.y) );


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
    float playerOffSetX = this->playerBrickTex.getSize().x/2;
    float playerOffSety = this->playerBrickTex.getSize().y/2;
    this->playerBrickSpr.setPosition(getPosition().x-playerOffSetX, getPosition().y-playerOffSety);
    float scaleFactor = (currentSpeed+movescaleAdjust)/(DEFAULTSPEED+movescaleAdjust);
    playerBrickSpr.setScale(scaleFactor,scaleFactor);
    return this->playerBrickSpr;
}
Sprite Player::displayPic() {
    Sprite playerspr;
    playerspr.setTexture(playerTexture);
    playerspr.setPosition(700,100*myID);
    return playerspr;
}

Sprite Player::displayShadow() {
    Sprite shadowSprite;
    shadowSprite.setTexture(playerBrickTex);

    float scaleFactor = (currentSpeed+movescaleAdjust)/(DEFAULTSPEED+movescaleAdjust);
    float displacement = (-1 + scaleFactor) * 15;
    float playerOffSetX = this->playerBrickTex.getSize().x/4  ;
    float playerOffSety = this->playerBrickTex.getSize().y/2;
    shadowSprite.setPosition((getPosition().x - playerOffSetX) + displacement , getPosition().y-playerOffSety);
    shadowSprite.setScale(scaleFactor,scaleFactor);
    shadowSprite.setColor(Color(0,0,0,200 - 50 * (scaleFactor-1)));
    return shadowSprite;
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
    moveTo(dest,myID);
}

void Player::moveTo(field *dest, int IDToLookFor) {

    if(dest != nullptr && hasPlayer) {
        //delete us on the field we are on
        if (tile != nullptr) {
            for (int i = 0; i < 6; i++) {
                if (tile && *(tile->playersOnField + i) == IDToLookFor) {
                    *(tile->playersOnField +
                      i) = FIELD_EMPTY; // we use -1 to denote that no players are on the this index of the array
                    break;
                }
            }
        }
        // then add us at the destination
        tile = dest;
        for(int j = 0 ; j < 6 ; j++) {
            if ( *(tile->playersOnField + j) == FIELD_EMPTY) {
                *(tile->playersOnField + j) = IDToLookFor;
            break;
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
void Player::setPic(int num){
    if(!this->playerTexture.loadFromFile("Client/Sprites/buttons/characters/"+to_string(num)+"/0.png")) {
        cout << "Error setting character pic";
    }
    if(!this->playerBrickTex.loadFromFile("Client/Sprites/player_sprites/"+to_string(num)+".png")) {
        cout << "Error setting character sprite";
    }
    playerBrickSpr.setTexture(playerBrickTex);
}
