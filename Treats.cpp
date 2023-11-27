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

Vector2 Treats::GetPosition() const{
    return position;
}

//void Treats::Update(){
//    position.y += speed;
//}

//bool Treats::CheckCollision(Vector2 snakePosition, float snakeRadius){
//    Rectangle treatCircle = {position.x, position.y, radius};
//    return CheckCollisionCircleRec(snakePosition, snakeRadius, treatCircle);
//}

//bool Treats::IsOutOfScreen(){
//    return position.y>GetScreenHeight() + size.y;
//}
