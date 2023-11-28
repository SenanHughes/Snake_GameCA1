#include "raylib.h"
#include "Snake.h"
#include "Treats.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "2nd Game Example");

    Snake player({screenWidth/2, screenHeight-50}, {20,20}, RAYWHITE);


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    int frameCount = 0;
    bool moveUpDown = false;
    bool moveLeftRight = false;
    bool gameOver = false; 
    Vector2 snakeDirection = {0,0};

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if(!gameOver)
        {
            if(IsKeyDown(KEY_UP)  && moveUpDown == false){
            snakeDirection = {0,-player.GetSize().y};
            moveUpDown = true;
            moveLeftRight = false;
            }

            if(IsKeyDown(KEY_DOWN) && moveUpDown == false){
            snakeDirection = {0,player.GetSize().y};
            moveUpDown = true;
            moveLeftRight = false;
            }

            if(IsKeyDown(KEY_LEFT) && moveLeftRight == false){
            snakeDirection = {-player.GetSize().x, 0};
            moveLeftRight = true;
            moveUpDown = false;
            }

            if(IsKeyDown(KEY_RIGHT) && moveLeftRight == false){
            snakeDirection = {player.GetSize().x, 0};
            moveLeftRight = true;
            moveUpDown = false;
            }

            if(frameCount%10 == 0){
                player.Move(snakeDirection);
            }

            if(player.GetPosition().y < 0 ||
                player.GetPosition().y > screenHeight - player.GetSize().y||
                player.GetPosition().x  == 0 ||
                player.GetPosition().x == screenWidth - player.GetSize().x){
                    gameOver = true;
                }

            frameCount++;
        }

        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            player.Draw();

            if(gameOver){
                DrawText("GAME OVER", screenWidth/2 -60, screenHeight/2,20, RED);
            }



        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
