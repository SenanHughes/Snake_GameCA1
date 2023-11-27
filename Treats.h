#ifndef TREATS_H
#define TREATS_H

#include "raylib.h"

class Treats{
    private:
    Vector2 position;
    float radius;
    Color color; 
    //float speed; 

    public:
    Treats(Vector2 pos, float r, Color c);//, float s);
    Treats();

    void Draw();

    Vector2 GetPosition() const;

    //void Update();

    //bool CheckCollision(Vector2 snakePosition, float snakeRadius);

    //bool IsOutOfScreen(); 
};

#endif