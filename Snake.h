#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"

class Snake{
    private:
    Vector2 position;
    Vector2 size;
    Color color;
    bool upDownDir;
    bool leftRightDir;

    public:
    Snake(Vector2 pos, Vector2 sz, Color c);
    Snake();

    void Draw();

    void Move(Vector2 offset);

    void SetPosition(Vector2 linkPosition);

    void movingDir(bool isUpDown, bool isLeftRight);

    bool returnUpDown() const;

    bool returnLeftRight() const;

    Vector2 GetPosition() const;

    Vector2 GetSize() const; 
};

#endif