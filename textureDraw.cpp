#include "textureDraw.h"

textureDraw::textureDraw(Texture2D bodyPart, Vector2 bodyPartPos, float rot, Color c)
:   bodyPartTexture(bodyPart),
    bodyPartPosition(bodyPartPos),
    textureRotation(rot),
    color(c){}

void textureDraw::drawProFunc(){
    DrawTexturePro(bodyPartTexture, (Rectangle){0, 0,(float)bodyPartTexture.width,(float)bodyPartTexture.height}, 
                        (Rectangle){bodyPartPosition.x+bodyPartTexture.width/2.0f, bodyPartPosition.y+bodyPartTexture.height/2.0f,(float)bodyPartTexture.width,(float)bodyPartTexture.height}, 
                        {bodyPartTexture.width/2.0f,bodyPartTexture.height/2.0f}, 
                        textureRotation, 
                        color);
}

void textureDraw::setTexture(Texture2D inputTexture){
    bodyPartTexture = inputTexture;
}

void textureDraw::setPos(Vector2 playerPosition){
    bodyPartPosition = playerPosition;
}

void textureDraw::setRot(float inputRot){
    textureRotation = inputRot;
}