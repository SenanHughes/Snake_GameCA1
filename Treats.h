#ifndef TREATS_H
#define TREATS_H

#include "raylib.h"

// This source file originated from the Obstacle header file from https://github.com/naoisecollins/2023MSc-SoftwareEngineering1-Second-Game
// Initially starting with the Draw & GetPosition functions before adding the newTreatLoc function to reposition the Apples across the screen 

class Treats{
    private:
    Texture2D texture;
    Vector2 position;
    Vector2 size;
    Color color; 
    
    public:
    Treats(Texture2D texture, Vector2 pos, Vector2 sz, Color c);

    void Draw();

    Vector2 GetPosition() const;

    void newTreatLoc(Vector2 offset);
};

#endif