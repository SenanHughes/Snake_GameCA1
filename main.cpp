#include "raylib.h"
#include "Snake.h"
#include "Treats.h"
#include "stdio.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1000;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "2nd Game Example");

    //Treats tastyTreat({(float)GetRandomValue(0,screenWidth- 20), (float)GetRandomValue(0,screenHeight-20)}, (20,20),PINK);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    bool singleKeyPress = true;
    bool gameOver = false;
    bool snakeGrow = false;
    int frameCount = 0;
    float actorSize = 20.0f;
    int snakeSize = 256;
    int snakeLength = 1;
    Vector2 snakeDirection = {0,0};
    Vector2 previousSnakeSection[snakeSize] = {0,0};
    
    Snake player[snakeSize];

    for(int i = 0; i < snakeSize; i++){
        player[i] = Snake({screenWidth/2.0f, screenHeight/2.0f}, {20,20}, RAYWHITE);
        //player[i] = Snake({0,0},{0,0},BLANK);
    }
    for(int i = 1; i < snakeSize; i++){
        player[i].SetPosition({-actorSize,-actorSize});
    }
    Treats tastyTreat({GetRandomValue(0, (screenWidth/actorSize)-1)*actorSize, GetRandomValue(0, (screenHeight/actorSize)-1)*actorSize},{20,20},PINK);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if(!gameOver)
        {
            if(IsKeyPressed(KEY_UP) && snakeDirection.y == 0 && singleKeyPress){
            snakeDirection = {0,-actorSize};
            singleKeyPress = false;
            }

            if(IsKeyPressed(KEY_DOWN) && snakeDirection.y == 0 && singleKeyPress){
            snakeDirection = {0,actorSize};
            singleKeyPress = false;
            }

            if(IsKeyPressed(KEY_LEFT) && snakeDirection.x == 0 && singleKeyPress){
            snakeDirection = {-actorSize, 0};
            singleKeyPress = false;
            }

            if(IsKeyPressed(KEY_RIGHT) && snakeDirection.x == 0 && singleKeyPress){
            snakeDirection = {actorSize, 0};
            singleKeyPress = false;
            }


            for(int i = 0; i < snakeLength; i++){
                previousSnakeSection[i] = player[i].GetPosition();
            }

            if(frameCount%5 == 0){
                for(int i = 0; i < snakeLength; i++){
                    if(i == 0){
                        player[i].Move(snakeDirection);
                    }
                    else{
                        player[i].SetPosition(previousSnakeSection[i-1]);
                    }
                }
                singleKeyPress = true;
            }
            
            if(player[0].GetPosition().x == tastyTreat.GetPosition().x && player[0].GetPosition().y == tastyTreat.GetPosition().y){
                tastyTreat.newTreatLoc({GetRandomValue(0, (screenWidth/actorSize)-1)*actorSize, GetRandomValue(0, (screenHeight/actorSize)-1)*actorSize});
                snakeLength++;
                player[snakeLength].SetPosition(player[snakeLength-1].GetPosition());
            }

            if(player[0].GetPosition().y < 0 ||
                player[0].GetPosition().y > screenHeight - player[0].GetSize().y||
                player[0].GetPosition().x  < 0 ||
                player[0].GetPosition().x > screenWidth - player[0].GetSize().x){
                    gameOver = true;
            }

            //if(player[0])

            frameCount++;
        }

        

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            //if(snakeSize == 0){
                //player[0].Draw();
            //    DrawRectangleV(player[0].GetPosition,player[0].GetSize,RAYWHITE);
            for(int i = 0; i < snakeLength; i++){
                //player[i].Draw();
                DrawRectangleV(player[i].GetPosition(), {actorSize,actorSize}, RAYWHITE);
            }
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
