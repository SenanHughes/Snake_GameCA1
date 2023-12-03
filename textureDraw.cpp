#include "textureDraw.h"


// Defining inputs for textureDraw initialisation
textureDraw::textureDraw(Texture2D bodyPart, Vector2 bodyPartPos, float rot, Color c)
:   bodyPartTexture(bodyPart),
    bodyPartPosition(bodyPartPos),
    textureRotation(rot),
    color(c){}

// Function to call the DrawTexturePro function with the correct inputs based on the constructor
void textureDraw::drawProFunc(){
    DrawTexturePro(bodyPartTexture, (Rectangle){0, 0,(float)bodyPartTexture.width,(float)bodyPartTexture.height}, 
                        (Rectangle){bodyPartPosition.x+bodyPartTexture.width/2.0f, bodyPartPosition.y+bodyPartTexture.height/2.0f,(float)bodyPartTexture.width,(float)bodyPartTexture.height}, 
                        {bodyPartTexture.width/2.0f,bodyPartTexture.height/2.0f}, 
                        textureRotation, 
                        color);
}

// Changing the Texture, so the above function can be reused across multiple portions of the main code
void textureDraw::setTexture(Texture2D inputTexture){
    bodyPartTexture = inputTexture;
}

// Changing the Position for the above reason 
void textureDraw::setPos(Vector2 playerPosition){
    bodyPartPosition = playerPosition;
}

// Changing the rotation to match the texture to the right orientation
void textureDraw::setRot(float inputRot){
    textureRotation = inputRot;
}