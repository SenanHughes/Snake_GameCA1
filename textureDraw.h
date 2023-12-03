#ifndef TEXTUREDRAW_H
#define TEXTUREDRAW_H

#include "raylib.h"

//Defining Class for textureDraw
class textureDraw{
    private:
    Texture2D bodyPartTexture;
    Vector2 bodyPartPosition;
    float textureRotation;
    Color color;

    public:
    // The Constructor for initialising the object in the main code
    textureDraw(Texture2D bodyPart, Vector2 bodyPartPos, float rot, Color c);

    // A function that will be used to implement the "DrawTexturePro" raylib feature
    void drawProFunc();

    // Chaniging the Texture to the correct one for each use
    void setTexture(Texture2D inputTexture);

    // Getting the position the Texture will be applied to
    void setPos(Vector2 playerPosition);

    // Determining if the texture needs to be rotated
    void setRot(float inputRot);
};

#endif