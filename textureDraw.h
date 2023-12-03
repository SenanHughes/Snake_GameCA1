#ifndef TEXTUREDRAW_H
#define TEXTUREDRAW_H

#include "raylib.h"

class textureDraw{
    private:
    Texture2D bodyPartTexture;
    Vector2 bodyPartPosition;
    float textureRotation;
    Color color;

    public:
    textureDraw(Texture2D bodyPart, Vector2 bodyPartPos, float rot, Color c);

    void drawProFunc();

    void setTexture(Texture2D inputTexture);

    void setPos(Vector2 playerPosition);

    void setRot(float inputRot);
};

#endif