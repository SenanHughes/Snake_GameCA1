#include "Treats.h"

Treats::Treats(Vector2 pos, Vector2 sz, Color c)
:   position(pos),
    size(sz),
    color(c){}

//Treats::Treats(): position ({0,0}), size({0,0}), color(BLANK) {}

void Treats::Draw(){
    DrawRectangleV(position, size, color);
}

//void Treats::Update(){
//    position.y += speed;
//}

//bool Treats::CheckCollision(Vector2 ballPosition, float ballRadius){
//    Rectangle TreatsRect = {position.x, position.y, size.x, size.y};
//    return CheckCollisionCircleRec(ballPosition, ballRadius, TreatsRect);
//}

//bool Treats::IsOutOfScreen(){
//    return position.y>GetScreenHeight() + size.y;
//}
