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

void Snake::movingDir(bool isUpDown, bool isLeftRight){
    upDownDir = isUpDown;
    leftRightDir = isLeftRight;
}

Vector2 Snake::GetPosition() const{
    return position;
}

Vector2 Snake::GetSize() const{
    return size;
}

bool Snake::returnUpDown() const{
    return upDownDir;
}

bool Snake::returnLeftRight() const{
    return leftRightDir;
}
