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

    //Treats tastyTreat({(float)GetRandomValue(0,screenWidth- 20), (float)GetRandomValue(0,screenHeight-20)}, (20,20),PINK);

    

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    int frameCount = 0;
    int actorSize = 20;
    bool moveUpDown = false;
    bool moveLeftRight = false;
    bool gameOver = false; 
    Vector2 snakeDirection = {0,0};
    Vector2 offset = {0,0};

    offset.x = screenWidth%actorSize;
    offset.y = screenHeight%actorSize;
    
    Snake player({screenWidth/2, screenHeight-50}, {actorSize,actorSize}, RAYWHITE);
    Treats tastyTreat({GetRandomValue(0, (screenWidth/actorSize)-1)*actorSize+offset.x/2, GetRandomValue(0, (screenHeight/actorSize)-1)*actorSize+offset.y},{20,20},PINK);

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
            tastyTreat.Draw();

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
