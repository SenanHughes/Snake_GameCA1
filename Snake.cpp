#include "Snake.h"

Snake::Snake(Vector2 pos, float r, Color c)
: position(pos),
    radius(r),
    color(c){}

void Snake::Draw(){
    DrawCircleV(position,radius,color);
}

void Snake::Move(Vector2 offset){
    position.x += offset.x;
    position.y += offset.y;
}

Vector2 Snake::GetPosition() const{
    return position;
}

float Snake::GetRadius() const{
    return radius;
}