#include <iostream>
#include <raylib.h>
using namespace std;

class PlayerAnimation {
    public:
        Image animation;
        Texture2D texture;
        int frameWidth;
        int frames;
        int playerSpeed;
        int frameHeight;
        int currentFrame;
        float frameTime;
        float timer;
        Rectangle frameRec;
        Vector2 position;

        PlayerAnimation(const char* image_path, int frames, int animSpeed)
        {
            this->animation = LoadImage(image_path);
            this->texture = LoadTextureFromImage(this->animation);
            this->frameWidth = this->texture.width / frames;
            this->frames = frames;
            this->frameHeight = this->texture.height;
            this->currentFrame = 0;
            this->frameTime = 1.0f / animSpeed;
            this->timer = 0.0f;
            this->frameRec = { 0.0f, 0.0f, (float)this->frameWidth, (float)this->frameHeight };
            this->position = { 100.0f, 300.0f };
            this->playerSpeed = 1;

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
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    //PLAYER WALKING ANIMATION
    PlayerAnimation player_walking("../textures/City_men_2/Walk.png", 10,15);

    //PLAYER IDLE ANIMATION
    PlayerAnimation player_idle = PlayerAnimation("../textures/City_men_2/Idle.png", 6,10);

    //PLAYER RUNNING ANIMATION
    PlayerAnimation player_running = PlayerAnimation("../textures/City_men_2/Run.png", 10,35);


    //Current player animation
    PlayerAnimation currentAnimation = player_idle;
 
    SetTargetFPS(60);         


    // Main game loop
    while (!WindowShouldClose())    
    {
        
       currentAnimation.update();

        if (IsKeyDown(KEY_LEFT_SHIFT)) {
        player_running.position.x = currentAnimation.position.x;
        player_running.position.x += player_running.playerSpeed * 8;  // Move player to the right at double speed
        currentAnimation = player_running;
        player_running.update();
        }
        else if (IsKeyDown(KEY_RIGHT)) {
            player_walking.position.x = currentAnimation.position.x;
            player_walking.position.x += player_walking.playerSpeed;  // Move player to the right at normal speed
            currentAnimation = player_walking;
            player_walking.update();
        }
        else {
            player_idle.position.x = currentAnimation.position.x;
            currentAnimation = player_idle;
            player_idle.update();
        }
    
        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            
            currentAnimation.draw();

        EndDrawing();
    }

    player_walking.unload();
    player_idle.unload();
    player_running.unload();

    CloseWindow();       
 
    return 0;
}

