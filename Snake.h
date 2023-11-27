#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"

class Snake{
    private:
    Vector2 position;
    float radius;
    Color color;

    public:
    Snake(Vector2 pos, float r, Color c);

    void Draw();

    void Move(Vector2 offset);

    Vector2 GetPosition() const;

    float GetRadius() const; 
};

#endif