#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"

class Snake{
    private:
    Vector2 position;
    Vector2 size;
    Color color;
    bool upDir;
    bool leftDir;
    bool downDir;
    bool rightDir;

    public:
    Snake(Vector2 pos, Vector2 sz, Color c);
    Snake();

    void Draw();

    void Move(Vector2 offset);

    void SetPosition(Vector2 linkPosition);

    void movingDir(bool isUp, bool isLeft, bool isDown, bool isRight);

    bool returnDown() const;

    bool returnLeft() const;

    bool returnUp() const;

    bool returnRight() const;

    Vector2 GetPosition() const;

    Vector2 GetSize() const; 
};

#endif