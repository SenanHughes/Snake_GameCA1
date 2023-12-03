#include "Snake.h"

// This source file originated from the Ball source file from https://github.com/naoisecollins/2023MSc-SoftwareEngineering1-Second-Game
// Initially starting with the Draw, Move, GetPosition, SetPosition & Get Size functions before expanding with extra functionality 

Snake::Snake(Vector2 pos, Vector2 sz, Color c)
:   position(pos),
    size(sz),
    color(c){}

Snake::Snake(): position({0,0}), size({0,0}), color(BLANK) {}

// This moves the snake head forward by the defined offset - in this case actorSize on Main.
// it gets added to the position each time
void Snake::Move(Vector2 offset){
    position.x += offset.x;
    position.y += offset.y;
}

// This is used for the subsequent body portions, reassigning the position to keep the chunk following the path of the head
// as opposed to moving as a single line in x & y
void Snake::SetPosition(Vector2 linkPosition){
     position.x = linkPosition.x;
     position.y = linkPosition.y;
}

// Used for texture assignement, when snake is changing direction the various directions of each snake chunk are relevant
void Snake::movingDir(bool isUp, bool isLeft, bool isDown, bool isRight){
    upDir = isUp;
    leftDir = isLeft;
    downDir = isDown;
    rightDir = isRight;
}

Vector2 Snake::GetPosition() const{
    return position;
}

bool Snake::returnDown() const{
    return downDir;
}

bool Snake::returnLeft() const{
    return leftDir;
}

bool Snake::returnUp() const{
    return upDir;
}

bool Snake::returnRight() const{
    return rightDir;
}
