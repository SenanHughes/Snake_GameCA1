#ifndef TREATS_H
#define TREATS_H

#include "raylib.h"

class Treats{
    private:
    Vector2 position;
    float radius;
    Color color;

    public:
    Treats(Vector2 pos, float r, Color c);
    Treats();

    void Draw();

    Vector2 GetPosition();
    
    float Size() const;

    void Move(Vector2 offset);

    //bool CheckCollision(Vector2 snakePos, float snakeRad);
};

#endif