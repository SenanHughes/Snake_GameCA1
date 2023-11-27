// The Base of this project is from the Ball & Obstacle game made during the lectures
// Using the existing structure and adapting functionality where required to work as a Snake game variant

#include "raylib.h"
#include "Snake.h"
#include "Treats.h"

//const int MAX_OBSTACLES = 10;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "SnakeCA");

    Snake player({screenWidth/2, screenHeight-50}, 20, RAYWHITE);
    Treats treatEat({screenWidth/2, screenHeight-110}, 20, PINK);
    //Treats treatEat({(int)GetRandomValue(0+20,screenWidth-20),(int)(0+20,screenHeight-20)}, 20, PINK);
    
    //for(int i = 0; i<MAX_OBSTACLES; ++i){
    //    float width = GetRandomValue(50,200);
    //    obstacles[i] = Obstacle({(float)GetRandomValue(0,screenWidth-(int)width), (float)(-20.0f-i*60)}, {width, 20.f}, RED, 4.0f);
    //}
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    int framesCounter = 0;
    int radConst = 20;
    bool movingUpDown = false;
    bool movingLeftRight = false;
    Vector2 moveSpeed = {0,0};
    bool gameOver = false; 
    bool tastyTreat = true;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if(!gameOver)
        // This block defines the movement of the player character - basic sphere, a further block will be defined to control the movement of the body on a delay
        {
            if(IsKeyDown(KEY_UP) && !movingUpDown){
            moveSpeed = {0, -radConst};
            movingUpDown = true;
            movingLeftRight = false;
            }
            if(IsKeyDown(KEY_DOWN) && !movingUpDown){
            moveSpeed = {0, radConst};
            movingUpDown = true;
            movingLeftRight = false;
            }
            if(IsKeyDown(KEY_RIGHT) && !movingLeftRight){
            moveSpeed = {radConst, 0};
            movingLeftRight = true;
            movingUpDown = false;
            }
            if(IsKeyDown(KEY_LEFT) && !movingLeftRight){
            moveSpeed = {-radConst, 0};
            movingLeftRight = true;
            movingUpDown = false;
            }

            if(framesCounter%5 == 0){
                player.Move(moveSpeed);
                
                if(player.GetPosition().x == treatEat.GetPosition().x && player.GetPosition().y == treatEat.GetPosition().y){
                tastyTreat = false;
                }
            }

        

            framesCounter++;
        }
        //for(int i= 0; i< MAX_OBSTACLES; ++i){
        //    if(obstacles[i].IsOutOfScreen()){
        //        float width = GetRandomValue(50,200);
        //        obstacles[i] = Obstacle({(float)GetRandomValue(0,screenWidth - (int)width), -20.0f},
        //        {width, 20.0f}, RED, 4.0f);
        //   }
        //    obstacles[i].Update();

        // This block checks to see whether the player collides with the edges of the screen and ends the game if so
        if(player.GetPosition().y == 0 + player.GetRadius() || 
            player.GetPosition().y == screenHeight - player.GetRadius() ||
            player.GetPosition().x == 0 + player.GetRadius() ||
            player.GetPosition().x == screenWidth - player.GetRadius()){
            gameOver = true;
        }

        if(!tastyTreat){
            tastyTreat = true;
            Treats treatEat({(int)GetRandomValue(0+20,screenWidth-20),(int)(0+20,screenHeight-20)}, 20, PINK);
        }

        //if(player.GetPosition().x == treatEat.GetPosition().x && player.GetPosition().y == treatEat.GetPosition().y){
        //    tastyTreat = false;
        //}


        //    if(obstacles[i].CheckCollision(player.GetPosition(), player.GetRadius())){
        //        gameOver = true;
        //    }
        //    score++;
        //
        //}
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            player.Draw();
            treatEat.Draw();
            //for(int i = 0; i<MAX_OBSTACLES; ++i){
            //    obstacles[i].Draw();
            //}

            //DrawText(TextFormat("Score: %i", score), 10,10,20, RAYWHITE);

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
