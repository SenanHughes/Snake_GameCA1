#ifndef TREATS_H
#define TREATS_H

#include "raylib.h"

class Treats{
    private:
    Vector2 position;
    Vector2 size;
    Color color; 

    public:
    Treats(Vector2 pos, Vector2 sz, Color c);
    //Treats();

    void Draw();

    //void Update();

    //bool CheckCollision(Vector2 ballPosition, float ballRadius);

    //bool IsOutOfScreen(); 
};

#endif