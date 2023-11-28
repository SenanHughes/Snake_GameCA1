#include "Treats.h"

Treats::Treats(Vector2 pos, float r, Color c)//, float s)
:   position(pos),
    radius(r),
    color(c){}
//    speed(s){}

Treats::Treats(): position ({0,0}), radius(0), color(BLANK) {}

void Treats::Draw(){
    DrawCircleV(position, radius, color);
}

Vector2 Treats::GetPosition(){
    return position;
}

float Treats::Size() const{
    return radius;
}
