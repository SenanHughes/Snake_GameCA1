#include "Treats.h"

// This source file originated from the Obstacle Source file from https://github.com/naoisecollins/2023MSc-SoftwareEngineering1-Second-Game
// Initially starting with the Draw & GetPosition functions before adding the newTreatLoc function to reposition the Apples across the screen

Treats::Treats(Texture2D texture, Vector2 pos, Vector2 sz, Color c)
:   texture(texture),
    position(pos),
    size(sz),
    color(c){}

// Draws in the texture at the defined position    
void Treats::Draw(){
    DrawTextureEx(texture, position, 0.0f, 1.25f, WHITE);
}

Vector2 Treats::GetPosition() const{
    return position;
}

// The position is randomly generated in main, offset is the newly random position
void Treats::newTreatLoc(Vector2 offset){
    position.x = offset.x;
    position.y = offset.y;
}
