#include "raylib.h"
#include "Snake.h"
#include "Treats.h"

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
    bool moveUpDown = false;
    bool moveLeftRight = false;
    bool gameOver = false; 
    bool updateTreat = false;
    bool snakeGrow = false;
    int frameCount = 0;
    int actorSize = 20;
    int snakeSize = 1;
    Vector2 snakeDirection = {0,0};
    
    Snake player[snakeSize];

    player[0] = Snake({screenWidth/2, screenHeight/2}, {actorSize,actorSize}, RAYWHITE);
    Treats tastyTreat({GetRandomValue(0, (screenWidth/actorSize)-1)*actorSize, GetRandomValue(0, (screenHeight/actorSize)-1)*actorSize},{20,20},PINK);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if(!gameOver)
        {
            if(IsKeyDown(KEY_UP)  && moveUpDown == false){
            snakeDirection = {0,-actorSize};
            moveUpDown = true;
            moveLeftRight = false;
            }

            if(IsKeyDown(KEY_DOWN) && moveUpDown == false){
            snakeDirection = {0,actorSize};
            moveUpDown = true;
            moveLeftRight = false;
            }

            if(IsKeyDown(KEY_LEFT) && moveLeftRight == false){
            snakeDirection = {-actorSize, 0};
            moveLeftRight = true;
            moveUpDown = false;
            }

            if(IsKeyDown(KEY_RIGHT) && moveLeftRight == false){
            snakeDirection = {actorSize, 0};
            moveLeftRight = true;
            moveUpDown = false;
            }

            if(frameCount%10 == 0){
                for(int i = 0; i < snakeSize; i++){
                    if(i == 0){
                        player[i].Move(snakeDirection);
                    }
                    else{
                        player[snakeSize].SetPosition(player[snakeSize-1].GetPosition());
                    }
                }
            }

            if(player[0].GetPosition().y < 0 ||
                player[0].GetPosition().y > screenHeight - player[0].GetSize().y||
                player[0].GetPosition().x  < 0 ||
                player[0].GetPosition().x > screenWidth - player[0].GetSize().x){
                    gameOver = true;
            }
            
            if(player[0].GetPosition().x == tastyTreat.GetPosition().x && player[0].GetPosition().y == tastyTreat.GetPosition().y && !updateTreat){
                tastyTreat.newTreatLoc({GetRandomValue(0, (screenWidth/actorSize)-1)*actorSize, GetRandomValue(0, (screenHeight/actorSize)-1)*actorSize});
                snakeGrow = true;
            //    updateTreat = true;
            }

            //if(snakeGrow){
            //    snakeSize++;
            //    player[snakeSize] = Snake({player[snakeSize-1].GetPosition().x - snakeDirection.x, player[snakeSize-1].GetPosition().y - snakeDirection.y}, {actorSize,actorSize}, RAYWHITE);
            //    //player[snakeSize].SetPosition(player[snakeSize-1].GetPosition());
            //}

            frameCount++;
        }

        

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            if(snakeSize < 1){
                player[0].Draw();
            }else {for(int i = 0; i < snakeSize; i++)
                player[i].Draw();
            }
            tastyTreat.Draw();


            //if(updateTreat){
            //    DrawText("drawtreat",0,20,50,YELLOW);
            //    tastyTreat.Draw();
            //    updateTreat = false;
            //}

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
