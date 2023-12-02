#include "Treats.h"

Treats::Treats(Texture2D texture, Vector2 pos, Vector2 sz, Color c)
//Treats::Treats(Vector2 pos, Vector2 sz, Color c)
:   texture(texture),
    position(pos),
    size(sz),
    color(c){}
void Treats::Draw(){
    //DrawRectangleV(position, size, color);
    DrawTextureEx(texture, position, 0.0f, 1.25f, WHITE);
}

Vector2 Treats::GetPosition() const{
    return position;
}

void Treats::newTreatLoc(Vector2 offset){
    position.x = offset.x;
    position.y = offset.y;
}
