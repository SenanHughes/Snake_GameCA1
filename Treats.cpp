#include "Treats.h"

Treats::Treats(Vector2 pos, Vector2 sz, Color c, float s)
:   position(pos),
    size(sz),
    color(c),
    speed(s){}

Treats::Treats(): position ({0,0}),size({0,0}), color(BLANK), speed(0.0f) {}

void Treats::Draw(){
    DrawRectangleV(position, size, color);
}

void Treats::Update(){
    position.y += speed;
}

bool Treats::CheckCollision(Vector2 ballPosition, float ballRadius){
    Rectangle TreatsRect = {position.x, position.y, size.x, size.y};
    return CheckCollisionCircleRec(ballPosition, ballRadius, TreatsRect);
}

bool Treats::IsOutOfScreen(){
    return position.y>GetScreenHeight() + size.y;
}
