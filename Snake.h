#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"

class Snake{
    private:
    Vector2 position;
    Vector2 size;
    Color color;

    public:
    Snake(Vector2 pos, Vector2 sz, Color c);

    void Draw();

    void Move(Vector2 offset);

    Vector2 GetPosition() const;

    Vector2 GetSize() const; 
};

#endif