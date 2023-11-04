#include "raylib.h"

struct Anim
{
    Rectangle rec; 
    Vector2 pos; 
    int frame; 
    float updateTime; 
    float runningTime;
};

int main()
{
    const int windowWidth{700};
    const int windowHeight{450};
    
    InitWindow(windowWidth, windowHeight, "First Game");

    const int gravity{1000};
    const int scarfyPadding{50};

    Texture2D obstacle = LoadTexture("Resources/Textures/Raylib_logo.png");
    Texture2D scarfy = LoadTexture("Resources/Textures/scarfy.png");

    Anim scarfyAnim; 
    scarfyAnim.rec.width = scarfy.width/6; 
    scarfyAnim.rec.height = scarfy.height; 
    scarfyAnim.rec.x = 0;
    scarfyAnim.rec.y = 0;
    scarfyAnim.pos.x = scarfyPadding; 
    scarfyAnim.pos.y = windowHeight - scarfyAnim.rec.height;
    scarfyAnim.frame = 0;
    scarfyAnim.updateTime = 1.0/12.0;
    scarfyAnim.runningTime = 0.0;

    Rectangle obRec; 
    obRec.width = obstacle.width;
    obRec.height = obstacle.height; 
    obRec.x = 0;
    obRec.y = 0;
    Vector2 obPos;
    obPos.x = windowWidth - obRec.width; 
    obPos.y = windowHeight - obRec.height; 

    int obVel{-100};

    int velocity{0};
    const int jumpHeight{500};
    bool jumped{false};
    int speed{200};
    bool collision{};

    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    { const float deltaTime{GetFrameTime()};

    Rectangle obstacleRec{
        obPos.x,
        obPos.y,
        obRec.width,
        obRec.height
    };

    Rectangle scarfyRec{
        scarfyAnim.pos.x,
        scarfyAnim.pos.y,
        scarfyAnim.rec.width,
        scarfyAnim.rec.height
    };

    if(CheckCollisionRecs(scarfyRec,obstacleRec))
    {
        collision = true; 
    }

    if(IsKeyDown(KEY_D) && !jumped){
        scarfyAnim.pos.x += speed* deltaTime;
        scarfyAnim.rec.width = scarfy.width/6;

        scarfyAnim.runningTime += deltaTime; 
        if(scarfyAnim.runningTime>= scarfyAnim.updateTime){
            scarfyAnim.runningTime = 0.0;
            scarfyAnim.rec.x = scarfyAnim.frame * scarfyAnim.rec.width;
            scarfyAnim.frame++;
            if(scarfyAnim.frame>5){
                scarfyAnim.frame = 0;
            }
        }
    }

    if(IsKeyReleased(KEY_D) && !jumped){
        scarfyAnim.frame = 0; 
        scarfyAnim.rec.x = scarfyAnim.frame * scarfyAnim.rec.width; 
    }

       if(IsKeyDown(KEY_A) && !jumped){
        scarfyAnim.pos.x -= speed* deltaTime;
        scarfyAnim.rec.width = -scarfy.width/6;

        scarfyAnim.runningTime += deltaTime; 
        if(scarfyAnim.runningTime>= scarfyAnim.updateTime){
            scarfyAnim.runningTime = 0.0;
            scarfyAnim.rec.x = scarfyAnim.frame * scarfyAnim.rec.width;
            scarfyAnim.frame++;
            if(scarfyAnim.frame>5){
                scarfyAnim.frame = 0;
            }
        }
    }

    if(IsKeyReleased(KEY_A) && !jumped){
        scarfyAnim.frame = 0; 
        scarfyAnim.rec.x = scarfyAnim.frame * scarfyAnim.rec.width; 
    }

    if(scarfyAnim.pos.y >= windowHeight - scarfy.height){
        velocity = 0;
        jumped = false; 
    }
    else {
        velocity += gravity * deltaTime; 
        jumped = true;
    }

    if(IsKeyPressed(KEY_SPACE)&& !jumped){
        velocity -= jumpHeight;
    }

    scarfyAnim.pos.y += velocity * deltaTime;

    obPos.x += obVel * deltaTime;

            BeginDrawing();
            ClearBackground(WHITE);

            if(!collision){
                DrawTextureRec(scarfy, scarfyAnim.rec, scarfyAnim.pos, WHITE);
                DrawTextureRec(obstacle,obRec, obPos, WHITE);
            }

            EndDrawing();        
                
    }

    UnloadTexture(scarfy);
    UnloadTexture(obstacle);
    CloseWindow();       
    return 0;       
            
}
