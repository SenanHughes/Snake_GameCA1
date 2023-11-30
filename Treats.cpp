#include "Treats.h"

Treats::Treats(Vector2 pos, Vector2 sz, Color c)
:   position(pos),
    size(sz),
    color(c){}

void Treats::Draw(){
    DrawRectangleV(position, size, color);
}

Vector2 Treats::GetPosition() const{
    return position;
}

void Treats::newTreatLoc(Vector2 offset){
    position.x = offset.x;
    position.y = offset.y;
}
