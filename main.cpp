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
    Rectangle hardBtn = {140,235,342,65};
    Rectangle softBtn = {540,235,330,65};
    Rectangle slowBtn = {70,395,145,65};
    Rectangle fastBtn = {270,395,155,65};
    Rectangle superSpeedyBtn = {490,395,445,65};
    Rectangle startBtn = {screenWidth/2-190,595,380,105};
    bool singleKeyPress = true;
    bool gameOver = false;
    bool gameStart = false;
    bool hardBorder = false;
    bool softBorder = false;
    bool slowBorder = false;
    bool fastBorder = false;
    bool superSpeedyBorder = false;
    int frameCount = 0;
    float actorSize = 20.0f;
    int snakeSize = 2000;
    int snakeLength = 1;
    int speedVal = 10;
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
        if(!gameStart){
            if(IsKeyPressed(KEY_P)){
                gameStart = true;
            }
        }

        if(!gameOver && gameStart)
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

            if(frameCount%speedVal == 0){
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
        if(!gameStart){
            ClearBackground(RAYWHITE);
            DrawText("Welcome to Snake", screenWidth/2-260, 60, 60, PINK);
            DrawText("Hard Walls", 150, 240, 60, BLACK);
            DrawText("Soft Walls", 550, 240, 60, BLACK);
            DrawText("Slow", 80, 400, 60, BLACK);
            DrawText("Fast", 280, 400, 60, BLACK);
            DrawText("Super Speedy", 500, 400, 60, BLACK);
            DrawText("START", screenWidth/2-180, 600, 100, GREEN);


            if(GetMousePosition().x > startBtn.x && GetMousePosition().x < startBtn.x + startBtn.width &&
                GetMousePosition().y > startBtn.y && GetMousePosition().y < startBtn.y + startBtn.height &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        gameStart = true;
                    }
            if(GetMousePosition().x > startBtn.x && GetMousePosition().x < startBtn.x + startBtn.width &&
                GetMousePosition().y > startBtn.y && GetMousePosition().y < startBtn.y + startBtn.height){
                    DrawRectangleLines(startBtn.x, startBtn.y, startBtn.width, startBtn.height ,RED);
                }
            
            if(GetMousePosition().x > hardBtn.x && GetMousePosition().x < hardBtn.x + hardBtn.width &&
                GetMousePosition().y > hardBtn.y && GetMousePosition().y < hardBtn.y + hardBtn.height &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        hardBorder = true;
                        softBorder = false;
                    }
            if(GetMousePosition().x > hardBtn.x && GetMousePosition().x < hardBtn.x + hardBtn.width &&
                GetMousePosition().y > hardBtn.y && GetMousePosition().y < hardBtn.y + hardBtn.height){
                    DrawRectangleLines(hardBtn.x, hardBtn.y, hardBtn.width, hardBtn.height ,RED);
                }

            if(GetMousePosition().x > softBtn.x && GetMousePosition().x < softBtn.x + softBtn.width &&
                GetMousePosition().y > softBtn.y && GetMousePosition().y < softBtn.y + softBtn.height &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        hardBorder = false;
                        softBorder = true;
                    }
            if(GetMousePosition().x > softBtn.x && GetMousePosition().x < softBtn.x + softBtn.width &&
                GetMousePosition().y > softBtn.y && GetMousePosition().y < softBtn.y + softBtn.height){
                    DrawRectangleLines(softBtn.x, softBtn.y, softBtn.width, softBtn.height ,RED);
                }
            
            if(GetMousePosition().x > slowBtn.x && GetMousePosition().x < slowBtn.x + slowBtn.width &&
                GetMousePosition().y > slowBtn.y && GetMousePosition().y < slowBtn.y + slowBtn.height &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        speedVal = 10;
                        slowBorder = true;
                        fastBorder = false;
                        superSpeedyBorder = false;
                    }
            if(GetMousePosition().x > slowBtn.x && GetMousePosition().x < slowBtn.x + slowBtn.width &&
                GetMousePosition().y > slowBtn.y && GetMousePosition().y < slowBtn.y + slowBtn.height){
                    DrawRectangleLines(slowBtn.x, slowBtn.y, slowBtn.width, slowBtn.height ,RED);
                }
            
            if(GetMousePosition().x > fastBtn.x && GetMousePosition().x < fastBtn.x + fastBtn.width &&
                GetMousePosition().y > fastBtn.y && GetMousePosition().y < fastBtn.y + fastBtn.height &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        speedVal = 5;
                        slowBorder = false;
                        fastBorder = true;
                        superSpeedyBorder = false;
                    }
            if(GetMousePosition().x > fastBtn.x && GetMousePosition().x < fastBtn.x + fastBtn.width &&
                GetMousePosition().y > fastBtn.y && GetMousePosition().y < fastBtn.y + fastBtn.height){
                    DrawRectangleLines(fastBtn.x, fastBtn.y, fastBtn.width, fastBtn.height ,RED);
                }
            
            if(GetMousePosition().x > superSpeedyBtn.x && GetMousePosition().x < superSpeedyBtn.x + superSpeedyBtn.width &&
                GetMousePosition().y > superSpeedyBtn.y && GetMousePosition().y < superSpeedyBtn.y + superSpeedyBtn.height &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        speedVal = 2;
                        slowBorder = false;
                        fastBorder = false;
                        superSpeedyBorder = true;
                    }
            if(GetMousePosition().x > superSpeedyBtn.x && GetMousePosition().x < superSpeedyBtn.x + superSpeedyBtn.width &&
                GetMousePosition().y > superSpeedyBtn.y && GetMousePosition().y < superSpeedyBtn.y + superSpeedyBtn.height){
                    DrawRectangleLines(superSpeedyBtn.x, superSpeedyBtn.y, superSpeedyBtn.width, superSpeedyBtn.height ,RED);
                }
                
            if(slowBorder == true){
                DrawRectangleLines(slowBtn.x, slowBtn.y, slowBtn.width, slowBtn.height ,RED);
            } else if(fastBorder == true){
                DrawRectangleLines(fastBtn.x, fastBtn.y, fastBtn.width, fastBtn.height ,RED);
            } else if(superSpeedyBorder == true){            
                DrawRectangleLines(superSpeedyBtn.x, superSpeedyBtn.y, superSpeedyBtn.width, superSpeedyBtn.height ,RED);
            }
            if(softBorder == true){
                DrawRectangleLines(softBtn.x, softBtn.y, softBtn.width, softBtn.height ,RED);
            } else if(hardBorder == true){
                DrawRectangleLines(hardBtn.x, hardBtn.y, hardBtn.width, hardBtn.height ,RED);
            }
        }
        else{
            ClearBackground(BLACK);

            for(int i = 0; i < snakeLength; i++){
                DrawRectangleV(player[i].GetPosition(), {actorSize,actorSize}, RAYWHITE);
            }
            tastyTreat.Draw();

            if(gameOver){
                DrawText("GAME OVER", screenWidth/2 -60, screenHeight/2,20, RED);
            }

            
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
