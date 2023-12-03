#include "raylib.h"
#include "Snake.h"
#include "Treats.h"
#include "textureDraw.h"

int main(void)
{
    // Declaring all Variables
    int screenWidth = 1000;
    int screenHeight = 800;
    Rectangle hardBtn = {140, 235, 342, 65};                               // border size for Hard Button on Start screen
    Rectangle softBtn = {540, 235, 330, 65};                               // border size for Soft Button on Start screen
    Rectangle slowBtn = {70, 395, 145, 65};                                // border size for Slow Button on Start screen
    Rectangle fastBtn = {270, 395, 155, 65};                               // border size for Fast Button on Start screen
    Rectangle superSpeedyBtn = {490, 395, 445, 65};                        // border size for Super Speedy Button on Start screen
    Rectangle startBtn = {(float)(screenWidth / 2) - 190, 595, 380, 105};  // border size for Start Button on Start screen
    Rectangle hardWalls = {0, 0, (float)screenWidth, (float)screenHeight}; // border size for the Hard Walls within the Game
    Rectangle yBtn = {415, 480, 40, 45};
    Rectangle nBtn = {530, 480, 40, 45};
    bool singleKeyPress = true;         // limit key presses within each snake movement
    bool gameOver = false;              // denote the end of game
    bool gameStart = false;             // denote the start of the game
    bool hardMode = true;               // if hard walls are selected
    bool softMode = false;              // if soft walls are selected
    bool slowBorder = true;             // if slow speed is selected
    bool fastBorder = false;            // if fast speed is selected
    bool superSpeedyBorder = false;     // if super speedy speed is selected
    bool up = false;                    // direction storage to ensure correct body textures are assigned
    bool left = false;                  //
    bool down = false;                  //
    bool right = false;                 //
    bool incSpeed = false;
    int frameCount = 0;                                       // initialises the frame count at 0
    float actorSize = 20.0f;                                  // sets the size of the snake sections
    int snakeSize = (screenHeight * screenWidth) / actorSize; // initialises the total size the snake could grow to - ratio of total screen pixels against snake section size
    int snakeLength = 1;                                      // intial snake size
    int speedVal = 10;                                        // initialising snake speed
    int startingSpeedVal = 10;
    int tongueAnim = 0;
    int tonguePos = 0;
    int lastScoreCount = 0;
    int scoreCount = 0;
    int scoreThreshold = 0;
    Vector2 snakeDirection = {0, 0};                  // intialising direction the snake moves
    Vector2 previousSnakeSection[snakeSize] = {0, 0}; // initialising the holder for previous snake positions
    bool previousSnakeUp[snakeSize] = {false};
    bool previousSnakeLeft[snakeSize] = {false};
    bool previousSnakeDown[snakeSize] = {false};
    bool previousSnakeRight[snakeSize] = {false};

    InitWindow(screenWidth, screenHeight, "SNAKE"); // starts the game window
    InitAudioDevice();

    // LoadingTextures in
    // Pixelated Apple Sprite sourced from itch.io, Author Santigou - https://santigou.itch.io/apple-sprite
    Texture2D tastyAppleTexture = LoadTexture("Resources/Textures/apple.png");

    // Pixelated Snake Sprite Sheet sourced from OpenGameArt.org, Author Blooming Pixels - https://opengameart.org/content/snake-sprite-sheet
    Texture2D snakeHead1Texture = LoadTexture("Resources/Textures/snakeHead_tongueIn.png");
    Texture2D snakeHead2Texture = LoadTexture("Resources/Textures/snakeHead_tongueMid.png");
    Texture2D snakeHead3Texture = LoadTexture("Resources/Textures/snakeHead_tongueOut.png");
    Texture2D snakeBodyTexture = LoadTexture("Resources/Textures/snakeBody.png");
    Texture2D snakeTailTexture = LoadTexture("Resources/Textures/snakeTail.png");
    Texture2D snakeBodyTurnTexture = LoadTexture("Resources/Textures/snakeBodyTurn.png");
    Texture2D snakeHeadAnim = snakeHead1Texture;

    // Ground Artwork sourced from OpenGameArt.org, Author GrumpyDiamond - https://opengameart.org/content/tilecraft-tile-set-ground
    Texture2D groundBackground = LoadTexture("Resources/Textures/groundTexture.png");

    // Loading Fonts in - using  LoadFontEx to allow the increase in size of loaded font to increase sharpness
    // Title Font sourced from fontspace.com, Author Amitsoni2410 - https://www.fontspace.com/serpens-font-f29969
    Font titleFont = LoadFontEx("Resources/Fonts/SerpensRegular-7MGE.ttf", 96, 0, 0);
    // Main Menu font sourced from fontspace.com, Author dustBUST - https://www.fontspace.com/sci-fied-font-f2527
    Font altFont = LoadFontEx("Resources/Fonts/SciFied2002-8OOn.ttf", 96, 0, 0);
    // Game Over Font sourced from fontspace.com, Author Dry Heaves - https://www.fontspace.com/raptor-kill-font-f4023
    Font gameOverFont = LoadFontEx("Resources/Fonts/RaptorKill-8aeg.ttf", 96, 0, 0);

    // Initialising the array for the player - using the Snake class
    Snake player[snakeSize];

    for (int i = 0; i < snakeSize; i++)
    {
        player[i] = Snake({screenWidth / 2.0f, screenHeight / 2.0f}, {20, 20}, RAYWHITE); // positions snake in the centre of the screen to start
    }
    for (int i = 1; i < snakeSize; i++)
    {
        player[i].SetPosition({-actorSize, -actorSize}); // storing the available snake body pieces off screen
    }

    // randomly positions the starting treat position
    Treats tastyTreat(tastyAppleTexture, {GetRandomValue(0, (screenWidth / actorSize) - 1) * actorSize, GetRandomValue(0, (screenHeight / actorSize) - 1) * actorSize}, {20, 20}, PINK);
    while (tastyTreat.GetPosition().x == screenWidth / 2.0f && tastyTreat.GetPosition().y == screenHeight / 2.0f)
    {
        tastyTreat.newTreatLoc({GetRandomValue(0, (screenWidth / actorSize) - 1) * actorSize, GetRandomValue(0, (screenHeight / actorSize) - 1) * actorSize});
    }

    // initialising function to draw the textures -
    textureDraw funcDraw(snakeHeadAnim, {0, 0}, 0.0f, WHITE);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Loading in Music & Sounds - Music for background tracks that loop, Sounds for sound effects - eating/ dying
    // Menu Music sourced from OpenGameArt.org, Author Matthew Pablo - https://opengameart.org/content/pleasant-creek
    Music menuTrack = LoadMusicStream("Resources/Music/Pleasant_Creek_Loop.wav");
    SetMusicVolume(menuTrack, 0.5f);
    // Game Music sourced from OpenGameArt.org, Author SubspaceAudio - https://opengameart.org/content/4-chiptunes-adventure
    Music gameTrack = LoadMusicStream("Resources/Music/Juhani_Junkala_[Chiptune Adventures]_2_Stage2.wav");
    SetMusicVolume(gameTrack, 0.5f);
    // Eating sound effect sourced from OpenGameArt.org, Author StarNinjas - https://opengameart.org/content/7-eating-crunches
    Sound eatingTreats = LoadSound("Resources/soundEffects/crunch3.wav");
    SetSoundVolume(eatingTreats, 1.0f);
    // Game Over sound effect sourced from OpenGameArt.org, Author den_yes - https://opengameart.org/content/game-over-soundold-school
    Sound gameOverSound = LoadSound("Resources/soundEffects/GameOver.wav");
    SetSoundVolume(gameOverSound, 1.0f);

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        // when gameOver hasn't been triggered and gameStart has been selected the main game begins
        if (!gameOver && !gameStart)
        {
            if (!IsMusicStreamPlaying(menuTrack))
            {
                PlayMusicStream(menuTrack);
            }
            else
            {
                UpdateMusicStream(menuTrack);
            }

            // Added just to give a bit of animation to the start screen - flicks through every 10 iterations to vary the displayed head texture
            if (tongueAnim % 10 == 0)
            {
                switch (tonguePos)
                {
                case 0:
                    snakeHeadAnim = snakeHead1Texture;
                    tonguePos++;
                    break;
                case 1:
                    snakeHeadAnim = snakeHead2Texture;
                    tonguePos++;
                    break;
                case 2:
                    snakeHeadAnim = snakeHead3Texture;
                    tonguePos = 0;
                    break;
                }
            }
            tongueAnim++;
        }

        if (!gameOver && gameStart)
        {
            StopMusicStream(menuTrack);
            if (!IsMusicStreamPlaying(gameTrack))
            {
                PlayMusicStream(gameTrack);
            }
            else
            {
                UpdateMusicStream(gameTrack);
            }
            // the movement control of the snake - up and down are positive and negative versions of the size of the snake head, left and right copy the same concept
            // Movement approach originated from Snake Raylib Game - https://github.com/raysan5/raylib-games/blob/master/classics/src/snake.c
            if (IsKeyPressed(KEY_UP) && snakeDirection.y == 0 && singleKeyPress)
            {
                snakeDirection = {0, -actorSize};
                singleKeyPress = false; // this bool prevents the keys being pressed so fast that the snake would move backwards along it's current line
                up = true;              // the following four bools are needed for the texture drawing further down, by assigning a direction to each portion of the snake
                left = false;           // when the snake is changing direction it allows the SnakeBodyTurn texture to be oriented appropriately
                down = false;
                right = false;
            }
            
            // At the start of each Game session the speedValue & score are reset - mostly relevant for Play Again
            if(frameCount == 0){
                speedVal = startingSpeedVal;
                lastScoreCount = 0;
                scoreCount = 0;
                // Depending on the speed difficulty chosen, the rate at which the snake will pick up speed varies - higher value = more apples needing to be consumed
                if(slowBorder){
                    scoreThreshold = 1000;
                } else if(fastBorder){
                    scoreThreshold = 2000;
                } else{
                    scoreThreshold = 4000;
                }
            } 

            if (IsKeyPressed(KEY_DOWN) && snakeDirection.y == 0 && singleKeyPress)
            {
                snakeDirection = {0, actorSize};
                singleKeyPress = false;
                up = false;
                left = false;
                down = true;
                right = false;
            }

            if (IsKeyPressed(KEY_LEFT) && snakeDirection.x == 0 && singleKeyPress)
            {
                snakeDirection = {-actorSize, 0};
                singleKeyPress = false;
                up = false;
                left = true;
                down = false;
                right = false;
            }

            if (IsKeyPressed(KEY_RIGHT) && snakeDirection.x == 0 && singleKeyPress)
            {
                snakeDirection = {actorSize, 0};
                singleKeyPress = false;
                up = false;
                left = false;
                down = false;
                right = true;
            }

            // assigns the position for each section of the snake to a temporary variable before the snake moves to allow each section to follow correctly
            for (int i = 0; i < snakeLength; i++)
            {
                previousSnakeSection[i] = player[i].GetPosition();
                previousSnakeUp[i] = player[i].returnUp();
                previousSnakeLeft[i] = player[i].returnLeft();
                previousSnakeDown[i] = player[i].returnDown();
                previousSnakeRight[i] = player[i].returnRight();
            }

            // waits for modulus of frame count and speed value to update the movement of the snake to give it the step by step movement the game had
            // Also guided by Raylib Example - https://github.com/raysan5/raylib-games/blob/master/classics/src/snake.c
            if (frameCount % speedVal == 0)
            {
                for (int i = 0; i < snakeLength; i++)
                {
                    if (i == 0)
                    {
                        player[i].Move(snakeDirection); // the head moves along the direction denoted in the above move section
                        player[i].movingDir(up, left, down, right);
                    }
                    else
                    {
                        player[i].SetPosition(previousSnakeSection[i - 1]); // the body follows the position of the previous body portion
                        player[i].movingDir(previousSnakeUp[i - 1], previousSnakeLeft[i - 1],
                                            previousSnakeDown[i - 1], previousSnakeRight[i - 1]);
                    }
                }
                singleKeyPress = true;
                // same functionality as the piece at the start menu, everytime the snake moves the tongue animation changes
                switch (tonguePos)
                {
                case 0:
                    snakeHeadAnim = snakeHead1Texture;
                    tonguePos++;
                    break;
                case 1:
                    snakeHeadAnim = snakeHead2Texture;
                    tonguePos++;
                    break;
                case 2:
                    snakeHeadAnim = snakeHead3Texture;
                    tonguePos = 0;
                    break;
                }
            }

            // treat location generation when collected
            if (player[0].GetPosition().x == tastyTreat.GetPosition().x && player[0].GetPosition().y == tastyTreat.GetPosition().y)
            {
                PlaySound(eatingTreats);
                // each time an apple is consumed the score goes up by 100
                scoreCount += 100;
                // when the score threshold has been reached, and a speed value greater than 1 the speed value will decrease and speed up the game
                // a reduction means a faster snake due to the less frames needed for a modulus of 0 in the Move functionality 
                if(scoreCount == lastScoreCount + scoreThreshold && speedVal > 1){
                    speedVal = speedVal - 1;
                    lastScoreCount = scoreCount;
                }
                tastyTreat.newTreatLoc({GetRandomValue(0, (screenWidth / actorSize) - 1) * actorSize, GetRandomValue(0, (screenHeight / actorSize) - 1) * actorSize});
                // condition to avoid placing the new treat where the snake body is
                // while loop to avoid placing treat where body is gained from raylib example - https://github.com/raysan5/raylib-games/blob/master/classics/src/snake.c
                for (int i = 0; i < snakeLength; i++)
                {
                    while (tastyTreat.GetPosition().x == player[i].GetPosition().x && tastyTreat.GetPosition().y == player[i].GetPosition().y)
                    {
                        tastyTreat.newTreatLoc({GetRandomValue(0, (screenWidth / actorSize) - 1) * actorSize, GetRandomValue(0, (screenHeight / actorSize) - 1) * actorSize});
                    };
                }
                snakeLength++;
                player[snakeLength].SetPosition(player[snakeLength - 1].GetPosition());
            }
            // gameOver for the hard walls variant if the snake hits the wall
            if (hardMode && (player[0].GetPosition().y < 0 ||
                             player[0].GetPosition().y > screenHeight - actorSize ||
                             player[0].GetPosition().x < 0 ||
                             player[0].GetPosition().x > screenWidth - actorSize))
            {
                gameOver = true;
                PlaySound(gameOverSound);
            }

            // no gameOver for soft walls variant, just teleports across from one side of the screen to the other
            if (softMode)
            {
                for (int i = 0; i < snakeLength; i++)
                {
                    if (player[i].GetPosition().y < 0 && snakeDirection.y < 0)
                    {
                        player[i].SetPosition({player[i].GetPosition().x, (float)screenHeight - actorSize});
                    }
                    else if (player[i].GetPosition().y > screenHeight - actorSize / 2 && snakeDirection.y > 0)
                    {
                        player[i].SetPosition({player[i].GetPosition().x, 0});
                    }
                    else if (player[i].GetPosition().x < 0 && snakeDirection.x < 0)
                    {
                        player[i].SetPosition({(float)screenWidth - actorSize, player[i].GetPosition().y});
                    }
                    else if (player[i].GetPosition().x > screenWidth - actorSize / 2 && snakeDirection.x > 0)
                    {
                        player[i].SetPosition({0, player[i].GetPosition().y});
                    }
                }
            }

            // gameOver for when the head collides with the body
            for (int i = 1; i < snakeLength; i++)
            {
                if (player[0].GetPosition().x == player[i].GetPosition().x && player[0].GetPosition().y == player[i].GetPosition().y)
                {
                    gameOver = true;
                    PlaySound(gameOverSound);
                }
            }
            frameCount++;
        }

        // conditions for gameOver menu
        if (gameOver)
        {
            // regardless of whether the player chooses to restart straight away or return to main menu these values get reinitialised
            tastyTreat.newTreatLoc({GetRandomValue(0, (screenWidth / actorSize) - 1) * actorSize, GetRandomValue(0, (screenHeight / actorSize) - 1) * actorSize});
            while (tastyTreat.GetPosition().x == screenWidth / 2.0f && tastyTreat.GetPosition().y == screenHeight / 2.0f)
            {
                tastyTreat.newTreatLoc({GetRandomValue(0, (screenWidth / actorSize) - 1) * actorSize, GetRandomValue(0, (screenHeight / actorSize) - 1) * actorSize});
            }
            singleKeyPress = true;
            frameCount = 0;
            actorSize = 20.0f;
            snakeSize = 2000;
            snakeLength = 1;
            snakeDirection = {0, 0};
            previousSnakeSection[snakeSize] = {0, 0};
            speedVal = startingSpeedVal;
            for (int i = 0; i < snakeSize; i++)
            {
                player[i] = Snake({screenWidth / 2.0f, screenHeight / 2.0f}, {20, 20}, RAYWHITE);
            }
            for (int i = 1; i < snakeSize; i++)
            {
                player[i].SetPosition({-actorSize, -actorSize});
            }
            // if they choose to restart gameOver is the only condition to clear
            if (IsKeyPressed(KEY_Y) || (GetMousePosition().x > yBtn.x &&
                                        GetMousePosition().x < yBtn.x + yBtn.width &&
                                        GetMousePosition().y > yBtn.y &&
                                        GetMousePosition().y < yBtn.y + yBtn.height &&
                                        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
            {
                gameOver = false;
            }
            else if (IsKeyPressed(KEY_N) || (GetMousePosition().x > nBtn.x &&
                                             GetMousePosition().x < nBtn.x + nBtn.width &&
                                             GetMousePosition().y > nBtn.y &&
                                             GetMousePosition().y < nBtn.y + nBtn.height &&
                                             IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
            { // if they choose not to restart gameOver and gameStart are reset to return to main menu
                gameStart = false;
                gameOver = false;
            }
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        if (!gameStart)
        {

            // start menu creation
            ClearBackground(BLANK);
            DrawTexture(groundBackground, 0, 0, WHITE);                                                  // adding the groundBackground to the screen
            DrawTextEx(titleFont, "Welcome to Snake", {screenWidth / 2.0f - 240.0f, 60}, 60, 0, YELLOW); // DrawTextEx was used here to allow loaded fonts to be displayed
            DrawTextEx(altFont, "Hard Walls", {150, 235}, 60, 0, RAYWHITE);
            DrawTextEx(altFont, "Soft Walls", {550, 235}, 60, 0, RAYWHITE);
            DrawTextEx(altFont, "Slow", {80, 395}, 60, 0, RAYWHITE);
            DrawTextEx(altFont, "Fast", {280, 395}, 60, 0, RAYWHITE);
            DrawTextEx(altFont, "Super Speedy", {500, 395}, 60, 0, RAYWHITE);
            DrawTextEx(altFont, "START", {screenWidth / 2.0f - 150.0f, 595}, 100, 0, GREEN);

            // purely an aesthetic inclusion, adding the game character below the main title
            DrawTexture(snakeHeadAnim, 500, 160, WHITE);
            DrawTexture(snakeBodyTexture, 500, 140, WHITE);
            DrawTexture(snakeTailTexture, 500, 120, WHITE);

            // while the mouse is somewhere within a box that covers the area of the text a red border box appears
            if (GetMousePosition().x > startBtn.x && GetMousePosition().x < startBtn.x + startBtn.width &&
                GetMousePosition().y > startBtn.y && GetMousePosition().y < startBtn.y + startBtn.height)
            {
                // when the player left clicks over Start the game starts
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    gameStart = true;
                }
            }

            // the following five top level if statements similarly have a temporary box highlighting the text when the mouse hovers over them
            // the difference is that when the button is clicked it sets a condition that impacts game play and also keeps the border around the text until gameStart
            if (GetMousePosition().x > hardBtn.x && GetMousePosition().x < hardBtn.x + hardBtn.width &&
                GetMousePosition().y > hardBtn.y && GetMousePosition().y < hardBtn.y + hardBtn.height)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    softMode = false;
                    hardMode = true; // sets the walls to be hard i.e. gameOver when hit
                }
            }

            if (GetMousePosition().x > softBtn.x && GetMousePosition().x < softBtn.x + softBtn.width &&
                GetMousePosition().y > softBtn.y && GetMousePosition().y < softBtn.y + softBtn.height)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    softMode = true; // sets the walls to be soft i.e. appear on opposite side of screen when travel through
                    hardMode = false;
                }
            }

            if (GetMousePosition().x > slowBtn.x && GetMousePosition().x < slowBtn.x + slowBtn.width &&
                GetMousePosition().y > slowBtn.y && GetMousePosition().y < slowBtn.y + slowBtn.height)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    startingSpeedVal = 10; // sets the speedVal to be the slowest iteration, for every 10 frames the snake moves
                    slowBorder = true;
                    fastBorder = false;
                    superSpeedyBorder = false;
                }
            }

            if (GetMousePosition().x > fastBtn.x && GetMousePosition().x < fastBtn.x + fastBtn.width &&
                GetMousePosition().y > fastBtn.y && GetMousePosition().y < fastBtn.y + fastBtn.height)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    startingSpeedVal = 5; // middle speed, every 5 frames the snake moves
                    slowBorder = false;
                    fastBorder = true;
                    superSpeedyBorder = false;
                }
            }

            if (GetMousePosition().x > superSpeedyBtn.x && GetMousePosition().x < superSpeedyBtn.x + superSpeedyBtn.width &&
                GetMousePosition().y > superSpeedyBtn.y && GetMousePosition().y < superSpeedyBtn.y + superSpeedyBtn.height)
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    startingSpeedVal = 2; // fastest speed, every 2 frames the snake moves
                    slowBorder = false;
                    fastBorder = false;
                    superSpeedyBorder = true;
                }
            }

            // using the bool set in the previous sections this keeps the border highlighted until a different option is selected or the game starts
            if (slowBorder)
            {
                DrawRectangleLines(slowBtn.x, slowBtn.y, slowBtn.width, slowBtn.height, RED);
            }
            else if (fastBorder)
            {
                DrawRectangleLines(fastBtn.x, fastBtn.y, fastBtn.width, fastBtn.height, RED);
            }
            else if (superSpeedyBorder)
            {
                DrawRectangleLines(superSpeedyBtn.x, superSpeedyBtn.y, superSpeedyBtn.width, superSpeedyBtn.height, RED);
            }
            if (softMode)
            {
                DrawRectangleLines(softBtn.x, softBtn.y, softBtn.width, softBtn.height, RED);
            }
            else if (hardMode)
            {
                DrawRectangleLines(hardBtn.x, hardBtn.y, hardBtn.width, hardBtn.height, RED);
            }
        }
        // Draws the game screen - snake moving, treats generated and walls to denote the hard wall variant if relevant
        else if (!gameOver)
        {
            ClearBackground(BLANK);
            DrawTexture(groundBackground, 0, 0, WHITE);

            DrawText(TextFormat("%d",slowBorder),60,60,60,BLACK);
            for (int i = 0; i < snakeLength; i++)
            {
                if (i == 0)
                {
                    funcDraw.setPos(player[i].GetPosition());
                    funcDraw.setTexture(snakeHeadAnim);
                    if (snakeDirection.y > 0)
                    {
                        funcDraw.setRot(0.0f);
                        funcDraw.drawProFunc();
                    }
                    else if (snakeDirection.y < 0)
                    {
                        funcDraw.setRot(180.0f);
                        funcDraw.drawProFunc();
                    }
                    else if (snakeDirection.x > 0)
                    {
                        funcDraw.setRot(270.0f);
                        funcDraw.drawProFunc();
                    }
                    else
                    {
                        funcDraw.setRot(90.0f);
                        funcDraw.drawProFunc();
                    }
                }
                else if ((player[i].returnRight() && player[i - 1].returnDown()) || (player[i].returnUp() && player[i - 1].returnLeft()))
                {
                    funcDraw.setPos(player[i].GetPosition());
                    funcDraw.setTexture(snakeBodyTurnTexture);
                    funcDraw.setRot(0.0f);
                    funcDraw.drawProFunc();
                }
                else if ((player[i].returnLeft() && player[i - 1].returnUp()) || (player[i].returnDown() && player[i - 1].returnRight()))
                {
                    funcDraw.setPos(player[i].GetPosition());
                    funcDraw.setTexture(snakeBodyTurnTexture);
                    funcDraw.setRot(180.0f);
                    funcDraw.drawProFunc();
                }
                else if ((player[i].returnLeft() && player[i - 1].returnDown()) || (player[i].returnUp() && player[i - 1].returnRight()))
                {
                    funcDraw.setPos(player[i].GetPosition());
                    funcDraw.setTexture(snakeBodyTurnTexture);
                    funcDraw.setRot(270.0f);
                    funcDraw.drawProFunc();
                }
                else if ((player[i].returnRight() && player[i - 1].returnUp()) || (player[i].returnDown() && player[i - 1].returnLeft()))
                {
                    funcDraw.setPos(player[i].GetPosition());
                    funcDraw.setTexture(snakeBodyTurnTexture);
                    funcDraw.setRot(90.0f);
                    funcDraw.drawProFunc();
                }
                else if (i > 0 && i != snakeLength - 1)
                {
                    funcDraw.setPos(player[i].GetPosition());
                    funcDraw.setTexture(snakeBodyTexture);
                    if (player[i].returnDown() && player[i - 1].returnDown())
                    {
                        funcDraw.setRot(0.0f);
                        funcDraw.drawProFunc();
                    }
                    else if (player[i].returnLeft() && player[i - 1].returnLeft())
                    {
                        funcDraw.setRot(90.0f);
                        funcDraw.drawProFunc();
                    }
                    else if (player[i].returnUp() && player[i - 1].returnUp())
                    {
                        funcDraw.setRot(180.0f);
                        funcDraw.drawProFunc();
                    }
                    else if (player[i].returnRight() && player[i - 1].returnRight())
                    {
                        funcDraw.setRot(270.0f);
                        funcDraw.drawProFunc();
                    }
                }
                else if (i == snakeLength - 1)
                {
                    funcDraw.setPos(player[i].GetPosition());
                    funcDraw.setTexture(snakeTailTexture);
                    if (player[i].GetPosition().y - player[i - 1].GetPosition().y < 0)
                    {
                        funcDraw.setRot(0.0f);
                        funcDraw.drawProFunc();
                    }
                    else if (player[i].GetPosition().y - player[i - 1].GetPosition().y > 0)
                    {
                        funcDraw.setRot(180.0f);
                        funcDraw.drawProFunc();
                    }
                    else if (player[i].GetPosition().x - player[i - 1].GetPosition().x > 0)
                    {
                        funcDraw.setRot(90.0f);
                        funcDraw.drawProFunc();
                    }
                    else
                    {
                        funcDraw.setRot(270.0f);
                        funcDraw.drawProFunc();
                    }
                }
            }

            tastyTreat.Draw();

            if (hardMode)
            {
                DrawRectangleLinesEx(hardWalls, 4.0f, DARKBROWN);
            }
        }

        // if the player dies - hits the wall/ itself game over is triggered, this menu allows the choice of playing again for the above functionality
        else if (gameOver)
        {
            ClearBackground(BLACK);

            if (gameOver)
            {
                DrawText(TextFormat("%i", scoreCount),screenWidth/2-(MeasureText(TextFormat("%i",scoreCount),60))/2,100,60, GREEN);
                DrawTextEx(gameOverFont, "GAME OVER", {screenWidth / 2.0f - 220.0f, screenHeight / 2.0f - 90.0f}, 90, 0, RED);
                DrawText("Play Again?", screenWidth / 2 - 175, screenHeight / 2, 60, RAYWHITE);
                DrawText("Y / N", screenWidth / 2 - 80, screenHeight / 2 + 80, 50, RAYWHITE);
            }
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadFont(gameOverFont);
    UnloadFont(titleFont);
    UnloadFont(altFont);
    UnloadTexture(tastyAppleTexture);
    UnloadTexture(snakeBodyTexture);
    UnloadTexture(snakeBodyTurnTexture);
    UnloadTexture(snakeHead1Texture);
    UnloadTexture(snakeHead2Texture);
    UnloadTexture(snakeHead3Texture);
    UnloadTexture(snakeHeadAnim);
    UnloadTexture(snakeTailTexture);
    UnloadTexture(groundBackground);
    UnloadMusicStream(gameTrack);
    UnloadMusicStream(menuTrack);
    UnloadSound(eatingTreats);
    UnloadSound(gameOverSound);

    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
