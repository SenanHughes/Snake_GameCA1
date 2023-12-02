#ifndef TREATS_H
#define TREATS_H

#include "raylib.h"

class Treats{
    private:
    Texture2D texture;
    Vector2 position;
    Vector2 size;
    Color color; 
    
    public:
    //Treats(Vector2 pos, Vector2 sz, Color c);
    Treats(Texture2D texture, Vector2 pos, Vector2 sz, Color c);

    void Draw();

    Vector2 GetPosition() const;

    void newTreatLoc(Vector2 offset);
};

#endif