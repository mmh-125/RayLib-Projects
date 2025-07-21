#include "raylib.h"
#include <stdio.h>

struct Boxs {
    Rectangle box;
    Color color;
    int score;
    bool active;
};

struct Ball {
    float radius;
    Vector2 center;
    Color color; 
    int x_speed;
    int y_speed;
};

struct paddle {
   Color colour;
    int x_pos;
    int x_speed;
    int y_pos;
    int width;
    int height;
   
};




//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
        
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;
    int row = 5;
    int column = 10;
    int boxWidth = (int) (screenWidth/column);
    int boxHeight = 20;
    int ballRadius = 10;
    Color colors[5] = {RED, ORANGE, YELLOW, GREEN, BLUE};
    int scores[5] = {10, 5, 3, 2, 1};
    int totalScore = 0;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    
    struct Boxs Enemies[row][column];
    struct Ball ball = {10.0, (Vector2) {screenWidth/2, screenHeight/2},BLACK, GetRandomValue(5,-5) , -4};
    
   
    
    struct paddle thisMover = {PINK, 350, 10, 700, 100, 20};
    
    
  
    
 
    
    
  
    for (int r = 0; r < row; r++) {
        
        for (int c = 0; c < column; c++) {
            Enemies[r][c].box = (Rectangle){ c * boxWidth, 60 + r * boxHeight, boxWidth - 2, boxHeight - 2 };
            
            
            
            Enemies[r][c].active = true;
            
            Enemies[r][c].color = colors[r];
            Enemies[r][c].score = scores[r];
            
          
          
        }
   
    
    
    
    }
    

    
    // Main game loop
    while (!WindowShouldClose() )    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------



        
        // Draw
        //-----------
     // -----------------------------------------------------------------------
      
        if (IsKeyDown(KEY_LEFT) == true && thisMover.x_pos > 0) {
            thisMover.x_pos -= thisMover.x_speed;
            
        }
        
        
        if (IsKeyDown(KEY_RIGHT) == true && thisMover.x_pos + thisMover.width < screenWidth) {
            thisMover.x_pos += thisMover.x_speed;
            
        }
        if (IsKeyDown(KEY_UP) == true && thisMover.y_pos > 600 ) {
            thisMover.y_pos -= 2;
            
        }
        if (IsKeyDown(KEY_DOWN) == true && thisMover.y_pos < 700 ) {
            thisMover.y_pos += 2;
            
        }
        
        
        for (int r = 0; r < row; r++) {
                    for (int c = 0; c < column; c++) {
                    
                        if (CheckCollisionCircleRec(ball.center, ball.radius, Enemies[r][c].box) == true && Enemies[r][c].active == true) {
                                Enemies[r][c].active = false;
                                ball.y_speed *= -1;
                                totalScore +=  scores[r];
                        }
                        
                    }
                       
        }
        
        if (ball.center.x < 0 || ball.center.x > screenWidth - ball.radius) {
            ball.x_speed *= -1;
        }
        
        
            
        
        if (ball.center.y < 0 ) {
            ball.y_speed *= -1;
        }
        
        Rectangle player = {thisMover.x_pos, thisMover.y_pos, thisMover.width, thisMover.height};
        
        
        
        if (CheckCollisionCircleRec(ball.center, ball.radius, player ) == true) {
            ball.y_speed *= -1;
            
                    
        }
        
        
       
        
        //if (ball.center.y < 0) {
          //  gameState = false;
       // }
        
        ball.center.x += ball.x_speed;
        ball.center.y += ball.y_speed;
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
                for (int r = 0; r < row; r++) {
                    for (int c = 0; c < column; c++) {
                        
                        if (Enemies[r][c].active == true) {
                            DrawRectangleRec(Enemies[r][c].box, Enemies[r][c].color);
                        }
                    }
                }
                DrawText(TextFormat("Score: %d", totalScore),20,20,20,BLACK);
                DrawRectangle(thisMover.x_pos,thisMover.y_pos,thisMover.width, thisMover.height, thisMover.colour);
                DrawLine(0, 600,800 , 600, RED);
                DrawLine(0, 720,800 , 720, RED);
                DrawCircleV(ball.center, ball.radius, ball.color);
                
                if (ball.center.y > screenHeight - ball.radius ) {
                    DrawText("YOU LOSE", 150, 400, 100 , RED);
                    
                    
            
                }
                if (totalScore == 210) {
                    ball.x_speed = 0;
                    ball.y_speed = 0;
                    DrawText("YOU WIN", 150, 400,100, GREEN);
                   
                   
                    
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