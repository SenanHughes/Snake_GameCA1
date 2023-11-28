#include "Snake.h"

Snake::Snake(Vector2 pos, Vector2 sz, Color c)
: position(pos),
    size(sz),
    color(c){}

void Snake::Draw(){
    DrawRectangleV(position, size, color);
}

void Snake::Move(Vector2 offset){
    position.x += offset.x;
    position.y += offset.y;
}

Vector2 Snake::GetPosition() const{
    return position;
}

Vector2 Snake::GetSize() const{
    return size;
}

