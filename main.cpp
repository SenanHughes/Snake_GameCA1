#include "raylib.h"
#include "Snake.h"
#include "Treats.h"
#include "stdio.h"

int main(void)
{
    // Declaring all Variables
    int screenWidth = 1000;
    int screenHeight = 800;
    Rectangle hardBtn = {140,235,342,65};                                       // border size for Hard Button on Start screen
    Rectangle softBtn = {540,235,330,65};                                       // border size for Soft Button on Start screen
    Rectangle slowBtn = {70,395,145,65};                                        // border size for Slow Button on Start screen
    Rectangle fastBtn = {270,395,155,65};                                       // border size for Fast Button on Start screen
    Rectangle superSpeedyBtn = {490,395,445,65};                                // border size for Super Speedy Button on Start screen
    Rectangle startBtn = {(float)(screenWidth/2) - 190, 595, 380, 105};         // border size for Start Button on Start screen
    Rectangle hardWalls = {0, 0, (float)screenWidth, (float)screenHeight};      // border size for the Hard Walls within the Game
    bool singleKeyPress = true;                             // limit key presses within each snake movement
    bool gameOver = false;                                  // denote the end of game
    bool gameStart = false;                                 // denote the start of the game
    bool hardMode = true;                                   // if hard walls are selected
    bool softMode = false;                                  // if soft walls are selected 
    bool slowBorder = true;                                 // if slow speed is selected
    bool fastBorder = false;                                // if fast speed is selected
    bool superSpeedyBorder = false;                         // if super speedy speed is selected
    int frameCount = 0;                                     // initialises the frame count at 0
    float actorSize = 20.0f;                                // sets the size of the snake sections
    int snakeSize = (screenHeight*screenWidth)/actorSize;   // initialises the total size the snake could grow to - ratio of total screen pixels against snake section size
    int snakeLength = 1;                                    // intial snake size
    int speedVal = 10;                                      // initialising snake speed
    Vector2 snakeDirection = {0,0};                         // intialising direction the snake moves
    Vector2 previousSnakeSection[snakeSize] = {0,0};        // initialising the holder for previous snake positions
    
    Texture2D tastyAppleTexture = LoadTexture("Resources/Textures/apple.png");

    Snake player[snakeSize];

    for(int i = 0; i < snakeSize; i++){
        player[i] = Snake({screenWidth/2.0f, screenHeight/2.0f}, {20,20}, RAYWHITE); // positions snake in the centre of the screen to start
    }
    for(int i = 1; i < snakeSize; i++){
        player[i].SetPosition({-actorSize,-actorSize}); // storing the available snake body pieces off screen
    }

    // randomly positions the starting treat position
    Treats tastyTreat({GetRandomValue(0, (screenWidth/actorSize)-1)*actorSize, GetRandomValue(0, (screenHeight/actorSize)-1)*actorSize}
                        , {20,20}
                        , PINK);
    //Treats tastyTreat(tastyAppleTexture
                        //, {GetRandomValue(0, (screenWidth/actorSize)-1)*actorSize, GetRandomValue(0, (screenHeight/actorSize)-1)*actorSize}
                        //, {20,20}
                        //, PINK);

    InitWindow(screenWidth, screenHeight, "SNAKE");         // starts the game window

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {   
        // when gameOver hasn't been triggered and gameStart has been selected the main game begins
        if(!gameOver && gameStart)
        {
            // the movement control of the snake - up and down are positive and negative versions of the size of the snake head, left and right copy the same concept
            if(IsKeyPressed(KEY_UP) && snakeDirection.y == 0 && singleKeyPress){
            snakeDirection = {0,-actorSize};
            singleKeyPress = false; // this bool prevents the keys being pressed so fast that the snake would move backwards along it's current line
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

            // assigns the position for each section of the snake to a temporary variable before the snake moves to allow each section to follow correctly
            for(int i = 0; i < snakeLength; i++){
                previousSnakeSection[i] = player[i].GetPosition();
            }

            // waits for modulus of frame count and speed value to update the movement of the snake to give it the step by step movement the game had
            if(frameCount%speedVal == 0){
                for(int i = 0; i < snakeLength; i++){
                    if(i == 0){
                        player[i].Move(snakeDirection); // the head moves along the direction denoted in the above move section
                    }
                    else{
                        player[i].SetPosition(previousSnakeSection[i-1]); // the body follows the position of the previous body portion
                    }
                }
                singleKeyPress = true;
            }
            

            // treat location generation when collected 
            if(player[0].GetPosition().x == tastyTreat.GetPosition().x && player[0].GetPosition().y == tastyTreat.GetPosition().y){
                tastyTreat.newTreatLoc({GetRandomValue(0, (screenWidth/actorSize)-1)*actorSize, GetRandomValue(0, (screenHeight/actorSize)-1)*actorSize});
                //condition to avoid placing the new treat where the snake body is
                for(int i = 0; i < snakeLength; i++){
                    while(tastyTreat.GetPosition().x == player[i].GetPosition().x && tastyTreat.GetPosition().y == player[i].GetPosition().y){
                        tastyTreat.newTreatLoc({GetRandomValue(0, (screenWidth/actorSize)-1)*actorSize, GetRandomValue(0, (screenHeight/actorSize)-1)*actorSize});
                    };
                }
                snakeLength++;
                player[snakeLength].SetPosition(player[snakeLength-1].GetPosition());
            }

            // gameOver for the hard walls variant if the snake hits the wall
            if(hardMode && (player[0].GetPosition().y < 0 ||
                player[0].GetPosition().y > screenHeight - player[0].GetSize().y||
                player[0].GetPosition().x  < 0 ||
                player[0].GetPosition().x > screenWidth - player[0].GetSize().x)){
                    gameOver = true;
            }

            // no gameOver for soft walls variant, just teleports across from one side of the screen to the other
            if(softMode){
                for(int i = 0; i < snakeLength; i++){
                    if(player[i].GetPosition().y < 0 && snakeDirection.y < 0){
                        player[i].SetPosition({player[i].GetPosition().x, (float)screenHeight - actorSize});
                    } else if(player[i].GetPosition().y > screenHeight - actorSize/2 && snakeDirection.y > 0){
                        player[i].SetPosition({player[i].GetPosition().x, 0});
                    } else if(player[i].GetPosition().x < 0 && snakeDirection.x < 0){
                        player[i].SetPosition({(float)screenWidth - actorSize, player[i].GetPosition().y});
                    } else if(player[i].GetPosition().x > screenWidth-actorSize/2 && snakeDirection.x > 0){
                        player[i].SetPosition({0, player[i].GetPosition().y});
                    }
                }
                
            }


            // gameOver for when the head collides with the body
            for(int i = 1; i < snakeLength; i++){
                if(player[0].GetPosition().x == player[i].GetPosition().x && player[0].GetPosition().y == player[i].GetPosition().y){
                    gameOver = true;
                }
            }
            frameCount++;
        }


        // conditions for gameOver menu
        if(gameOver){
            // regardless of whether the player chooses to restart straight away or return to main menu these values get reinitialised
            singleKeyPress = true;
            frameCount = 0;
            actorSize = 20.0f;
            snakeSize = 2000;
            snakeLength = 1;
            snakeDirection = {0,0};
            previousSnakeSection[snakeSize] = {0,0};
            for(int i = 0; i < snakeSize; i++){
                player[i] = Snake({screenWidth/2.0f, screenHeight/2.0f}, {20,20}, RAYWHITE);
            }
            for(int i = 1; i < snakeSize; i++){
                player[i].SetPosition({-actorSize,-actorSize});
            }
            // if they choose to restart gameOver is the only condition to clear
            if(IsKeyPressed(KEY_Y)){
                gameOver = false;
            } else if(IsKeyPressed(KEY_N)){ // if they choose not to restart gameOver and gameStart are reset to return to main menu
                gameStart = false;
                gameOver = false;
            }
        }
        

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        if(!gameStart){

            // start menu creation
            ClearBackground(RAYWHITE);
            DrawText("Welcome to Snake", screenWidth/2-260, 60, 60, PINK);
            DrawText("Hard Walls", 150, 240, 60, BLACK);
            DrawText("Soft Walls", 550, 240, 60, BLACK);
            DrawText("Slow", 80, 400, 60, BLACK);
            DrawText("Fast", 280, 400, 60, BLACK);
            DrawText("Super Speedy", 500, 400, 60, BLACK);
            DrawText("START", screenWidth/2-180, 600, 100, GREEN);

            // while the mouse is somewhere within a box that covers the area of the text a red border box appears
            if(GetMousePosition().x > startBtn.x && GetMousePosition().x < startBtn.x + startBtn.width &&
                GetMousePosition().y > startBtn.y && GetMousePosition().y < startBtn.y + startBtn.height){
                    DrawRectangleLines(startBtn.x, startBtn.y, startBtn.width, startBtn.height ,RED);
                    // when the player left clicks over Start the game starts
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        gameStart = true;
                    }
                }
            
            // the following five top level if statements similarly have a temporary box highlighting the text when the mouse hovers over them
            // the difference is that when the button is clicked it sets a condition that impacts game play and also keeps the border around the text until gameStart
            if(GetMousePosition().x > hardBtn.x && GetMousePosition().x < hardBtn.x + hardBtn.width &&
                GetMousePosition().y > hardBtn.y && GetMousePosition().y < hardBtn.y + hardBtn.height){
                    DrawRectangleLines(hardBtn.x, hardBtn.y, hardBtn.width, hardBtn.height ,RED);
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        softMode = false;
                        hardMode = true; // sets the walls to be hard i.e. gameOver when hit
                    }
                }

            if(GetMousePosition().x > softBtn.x && GetMousePosition().x < softBtn.x + softBtn.width &&
                GetMousePosition().y > softBtn.y && GetMousePosition().y < softBtn.y + softBtn.height){
                    DrawRectangleLines(softBtn.x, softBtn.y, softBtn.width, softBtn.height ,RED);
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        softMode = true; // sets the walls to be soft i.e. appear on opposite side of screen when travel through
                        hardMode = false;
                    }
                }
            
            if(GetMousePosition().x > slowBtn.x && GetMousePosition().x < slowBtn.x + slowBtn.width &&
                GetMousePosition().y > slowBtn.y && GetMousePosition().y < slowBtn.y + slowBtn.height){
                    DrawRectangleLines(slowBtn.x, slowBtn.y, slowBtn.width, slowBtn.height ,RED);
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        speedVal = 10; // sets the speedVal to be the slowest iteration, for every 10 frames the snake moves
                        slowBorder = true;
                        fastBorder = false;
                        superSpeedyBorder = false;
                    }
                }
            
            if(GetMousePosition().x > fastBtn.x && GetMousePosition().x < fastBtn.x + fastBtn.width &&
                GetMousePosition().y > fastBtn.y && GetMousePosition().y < fastBtn.y + fastBtn.height){
                    DrawRectangleLines(fastBtn.x, fastBtn.y, fastBtn.width, fastBtn.height ,RED);
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        speedVal = 5; // middle speed, every 5 frames the snake moves
                        slowBorder = false;
                        fastBorder = true;
                        superSpeedyBorder = false;
                    }
                }
            
            if(GetMousePosition().x > superSpeedyBtn.x && GetMousePosition().x < superSpeedyBtn.x + superSpeedyBtn.width &&
                GetMousePosition().y > superSpeedyBtn.y && GetMousePosition().y < superSpeedyBtn.y + superSpeedyBtn.height){
                    DrawRectangleLines(superSpeedyBtn.x, superSpeedyBtn.y, superSpeedyBtn.width, superSpeedyBtn.height ,RED);
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        speedVal = 2; // fastest speed, every 2 frames the snake moves
                        slowBorder = false;
                        fastBorder = false;
                        superSpeedyBorder = true;
                    }
                }
            
            // using the bool set in the previous sections this keeps the border highlighted until a different option is selected or the game starts    
            if(slowBorder){
                DrawRectangleLines(slowBtn.x, slowBtn.y, slowBtn.width, slowBtn.height ,RED);
            } else if(fastBorder){
                DrawRectangleLines(fastBtn.x, fastBtn.y, fastBtn.width, fastBtn.height ,RED);
            } else if(superSpeedyBorder ){            
                DrawRectangleLines(superSpeedyBtn.x, superSpeedyBtn.y, superSpeedyBtn.width, superSpeedyBtn.height ,RED);
            }
            if(softMode){
                DrawRectangleLines(softBtn.x, softBtn.y, softBtn.width, softBtn.height ,RED);
            } else if(hardMode){
                DrawRectangleLines(hardBtn.x, hardBtn.y, hardBtn.width, hardBtn.height ,RED);
            }
        }
        // Draws the game screen - snake moving, treats generated and walls to denote the hard wall variant if relevant
        else if(!gameOver){
            ClearBackground(BLACK);

            for(int i = 0; i < snakeLength; i++){
                DrawRectangleV(player[i].GetPosition(), {actorSize,actorSize}, RAYWHITE);
            }
            
            //tastyTreat.Draw();
            DrawTextureEx(tastyAppleTexture, {screenWidth/2.0f,screenHeight/2.0f}, 0.0f, 1.25f,WHITE);
            //DrawTextureRec(tastyAppleTexture, {0,0,0,0}, tastyTreat.GetPosition(), WHITE);

            if(hardMode){
                DrawRectangleLinesEx(hardWalls,3.0f, RED);
            }
            
        }

        // if the player dies - hits the wall/ itself game over is triggered, this menu allows the choice of playing again for the above functionality
        else if(gameOver){
            ClearBackground(BLACK);

            if(gameOver){
                DrawText("GAME OVER", screenWidth/2 - 180, screenHeight/2 - 80, 60, RED);
                DrawText("Play Again?", screenWidth/2 - 175, screenHeight/2, 60, RAYWHITE);
                DrawText("Y / N", screenWidth/2 - 110, screenHeight/2 + 80, 80, RAYWHITE);
            }
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(tastyAppleTexture);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
