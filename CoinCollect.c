/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute 'raylib_compile_execute' script
*   Note that compiled executable is placed in the same folder as .c file
*
*   To test the examples on Web, press F6 and execute 'raylib_compile_execute_web' script
*   Web version of the program is generated in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>



struct Player {
    int posX;
    int posY;
    int width;
    int height;
    Color color;
} ;

struct Coin {
    int posX;
    int posY;
    float radius;
    Color color;
};



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    
    struct Player RedBoi;
    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    RedBoi.posX = 0;
    RedBoi.height = 20;
    RedBoi.posY = 600 - RedBoi.height;
    RedBoi.width = 100;
    RedBoi.color = RED;

    // Coin 1
    struct Coin coin1;
    coin1.posX=40;
    coin1.posY=0;
    coin1.radius= 20.0;
    coin1.color=GOLD;

    int score;
    score = 0;
    int speed = 2;
    int lives = 3;
    bool end = false;
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        if (end == false){
            if (IsKeyDown(KEY_RIGHT) == true) {
                RedBoi.posX = RedBoi.posX + 10;
            }

        if (IsKeyDown(KEY_LEFT) == true) {
            RedBoi.posX = RedBoi.posX - 10;
        }
        
        
        // Checking if the player is colliding with the left wall, if so make him stop
        if (RedBoi.posX < 0) {
            RedBoi.posX = 0;
        }

        // Checking if the player is colliding with the left wall, if so make him stop
        if (RedBoi.posX > screenWidth - RedBoi.width) {
            RedBoi.posX = screenWidth - RedBoi.width;
        }
        // Checking if coin is coliding with the character.
        Vector2 CenterOfCoin = {(float)coin1.posX, (float)coin1.posY};
        Rectangle RecOfRedBoi = {(float)RedBoi.posX, (float)RedBoi.posY, (float)RedBoi.width, (float)RedBoi.height};
        
         
        if (CheckCollisionCircleRec(CenterOfCoin, coin1.radius, RecOfRedBoi) == true ) {
            score = score + 1;
            coin1.posY = 0;
            coin1.posX = GetRandomValue(0,800);
            speed += 1;
        }

        // Checking if coin is going off of screen 
        if (coin1.posY > screenHeight + (int)coin1.radius) {
            coin1.posY = 0;
            coin1.posX = GetRandomValue(0,800);
            speed += 1;
            lives -= 1;
        }
        
        

        coin1.posY = coin1.posY + speed;
        
        }
        
        // Draw
        //----------------------------------------------------------------------------------
        
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawRectangle(RedBoi.posX, RedBoi.posY, RedBoi.width, RedBoi.height, RedBoi.color);
            DrawCircle(coin1.posX, coin1.posY, coin1.radius, coin1.color);
            DrawText(TextFormat("Score %d", score), 20, 20, 20, BLACK);
             DrawText(TextFormat("Lives %d", lives), 20, 40, 20, BLACK);
             
             if (lives == 0) {
                DrawText("YOU LOSE", 150, 400, 100 , RED);
               
                end = true;
                
            
            }
            
             if (score == 10) {
                DrawText("YOU WIN", 150, 400, 100 , GREEN);
               
                end = true;
                
            
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