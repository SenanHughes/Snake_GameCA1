#include "Snake.h"

Snake::Snake(Vector2 pos, Vector2 sz, Color c)
:   position(pos),
    size(sz),
    color(c){}

Snake::Snake(): position({0,0}), size({0,0}), color(BLANK) {}

void Snake::Draw(){
    DrawRectangleV(position, size, color);
}

void Snake::Move(Vector2 offset){
    position.x += offset.x;
    position.y += offset.y;
}

void Snake::SetPosition(Vector2 linkPosition){
     position.x = linkPosition.x;
     position.y = linkPosition.y;
}

void Snake::movingDir(bool isUp, bool isLeft, bool isDown, bool isRight){
    upDir = isUp;
    leftDir = isLeft;
    downDir = isDown;
    rightDir = isRight;
}

Vector2 Snake::GetPosition() const{
    return position;
}

Vector2 Snake::GetSize() const{
    return size;
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
