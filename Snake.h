#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"

// This source file originated from the Ball header file from https://github.com/naoisecollins/2023MSc-SoftwareEngineering1-Second-Game
// Initially starting with the Draw, Move, GetPosition, SetPosition & Get Size functions before expanding with extra functionality 

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
    //Blank Constructor to allow the initialisation of an array to make each portion of the snake
    Snake();

    void Move(Vector2 offset);

    void SetPosition(Vector2 linkPosition);

    void movingDir(bool isUp, bool isLeft, bool isDown, bool isRight);

    Vector2 GetPosition() const;

    bool returnDown() const;

    bool returnLeft() const;

    bool returnUp() const;

    bool returnRight() const;
};

#endif