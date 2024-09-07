#include <iostream>
#include <raylib.h>
using namespace std;

class PlayerAnimation {
    public:
        Image animation;
        Texture2D texture;
        int frameWidth;
        int frames;
        int frameHeight;
        int currentFrame;
        float frameTime;
        float timer;
        Rectangle frameRec;
        Vector2 position;

        PlayerAnimation(const char* image_path, int frames)
        {
            this->animation = LoadImage(image_path);
            this->texture = LoadTextureFromImage(this->animation);
            this->frameWidth = this->texture.width / frames;
            this->frames = frames;
            this->frameHeight = this->texture.height;
            this->currentFrame = 0;
            this->frameTime = 0.1f;
            this->timer = 0.0f;
            this->frameRec = { 0.0f, 0.0f, (float)this->frameWidth, (float)this->frameHeight };
            this->position = { 400.0f, 300.0f };

            if(this->texture.id ==0){
                cout << "Failed to load texture.";
            }

            UnloadImage(this->animation);

        }

        void update(){
            this->timer += GetFrameTime();

            // Check if it's time to move to the next frame
            if (this->timer >= this->frameTime) {
                this->timer = 0.0f;  // Reset the timer
                this->currentFrame++;  // Move to the next frame

                if (this->currentFrame >= this->frames) this->currentFrame = 0;  // Loop back to the first frame
            }

            // Update the frame rectangle to display the current frame
            this->frameRec.x = (float)this->currentFrame * (float)this->frameWidth;
        }

        void draw(){
            DrawTextureRec(this->texture, this->frameRec, this->position, WHITE);

        }

        void unload(){
            UnloadTexture(this->texture);
        }

};


int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    //PLAYER WALKING ANIMATION
    PlayerAnimation player_walking("../textures/City_men_2/Walk.png", 10);

    //PLAYER IDLE ANIMATION
    Texture2D player_idle = LoadTexture("../textures/City_men_2/Idle.png");

    //PLAYER RUNNING ANIMATION
    Texture2D player_running = LoadTexture("../textures/City_men_2/Run.png");

 
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        player_walking.update();
    
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

           
            //PLAYER WALKING ANIMATION
            player_walking.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    player_walking.unload();
    UnloadTexture(player_idle);
    UnloadTexture(player_running);

    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

