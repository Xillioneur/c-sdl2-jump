# C SDl2 Jump - Episode 1 of Code Review

This is a short game of just jumping. No score. No hands or feet. Just jumping. Amen and selah to you all. Please play the game for free and not the monetary.

## Short Tutorial Series Begins Now

This will be a short tutorial series of 10 projects, including this one. May God bless us all and make this series blessed with prose and love and life. Amen and selah, if I don't finish this project, it will be updated to reflect the progress without changing this part. Amen and good day to you if you read this.

### Episode 1 - Jumping

Here is the code. Please copy and paste it into your file before you begin to see it run, and to understand the code first before you write it yourself. We do this for all the tutorials in the series.

```c
// main.c
#include <SDL2/SDL.h>
#include <stdio.h>

#define WIDTH 880
#define HEIGHT 600
#define GRAVITY 0.5
#define JUMP_VEL -10

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Pixel Jumper", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    float player_x = WIDTH / 2;
    float player_y = HEIGHT / 2;
    float vel_y = 0;
    int score = 0;
    int running = 1;
    int on_ground = 0;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                    case SDLK_SPACE:
                    if (on_ground) vel_y = JUMP_VEL;
                    break;
                }
            }
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_A] && player_x > 0) player_x -= 5;
        if (keys[SDL_SCANCODE_D] && player_x < WIDTH - 50) player_x += 5;
        
        vel_y += GRAVITY;
        player_y += vel_y;

        if (player_y >= HEIGHT - 50) {
            player_y = HEIGHT - 50;
            vel_y = 0;
            on_ground = -1;
        } else {
            on_ground = 0;
        }

        if (player_y > HEIGHT) {
            player_y = HEIGHT / 2;
            vel_y = 0;
            score = 0;
        }

        score++;

        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw player
        SDL_Rect player_rect = { (int)player_x, (int)player_y, 50, 50};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &player_rect);

        // Draw ground
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderDrawLine(renderer, 0, HEIGHT - 1, WIDTH, HEIGHT - 1);

        SDL_RenderPresent(renderer);

        // Delay for ~60 FPS
        SDL_Delay(16);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("Final Score: %d\n", score);
    return 0;
}
```

To run the code type:

```bash
gcc main.c -o pixel_jump -lSDL2
./pixel_jump
```

Please press play on your game and start now before you begin.

#### Code Review inspired by Grok and Written by Me

This is a code review of the code we just showed you. If you do not wish to rewrite the code and learn about it, just stop here, as you already have the code needed to understand everything. This is just to review for us all to understand Grok and everyone better who gives us the code for free.

##### Includes and Constants

This begins the code snippet with some headers that will be needed to write the game. Everything is included; proceed once you have written this down.

```c
#include <SDL2/SDL.h>
#include <stdio.h>
#define WIDTH 880
#define HEIGHT 600
#define GRAVITY 0.5
#define JUMP_VEL -10
```

##### Main Method and SDL Initialization

This will initialize your code for free using something simple and clean. You can make this as complicated as you want, but we are going to start with a simple `main` function, and that's all. The `main` function will serve as the entry point for all your code and can house everything you need to initialize. This is what starts your graphics window up and opens it for you to see and play. 

```c
int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Init failed: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Pixel Jumper",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
```

##### Game State Variables

These are the integers needed to fly and dance. However, since we want precision, we will be making them as floats.

```c
    float player_x = WIDTH / 2;
    float player_y = HEIGHT / 2;
    float vel_y = 0;
    int score = 0;
    int running = 1;
    int on_ground = 0;
```

##### Main Game Loop and Event Polling

The core loop runs while `running` is true. It polls for SDL events like window close or key presses. On quit, it sets `running` to 0. For key down events, Escape quits, and Space triggers a jump only if on ground (setting `vel_y` to the negative jump velocity). This handles discrete inputs efficiently without blocking. The loop's structure ensures responsive event handling before updating the game state.

```c
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                    case SDLK_SPACE:
                    if (on_ground) vel_y = JUMP_VEL;
                    break;
                }
            }
        }
```

##### Continuous Input and Horizontal Movement

Inside the loop, we have the controls, which are only moving left and moving right for now.

```c
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_A] && player_x > 0) player_x -= 5;
        if (keys[SDL_SCANCODE_D] && player_x < WIDTH - 50) player_x += 5;
```

##### Physics Update, Gravity, Position, and Collision

Next is the physics tick. Using gravity to control the vertical velocity, we then update the position and make it flat on the ground. When the player hits the ground `(y >= height - 50)` we snap to ground, set the velocity to zero, and set the `on_ground` variable to -1. If not on the ground, we simply set it to 0. This might be confusing, so ignore it as a variable. It's basically a boolean that is true at -1. When y exceeds the height, which means the player is falling, we reset the player to the center, set the velocity to zero, and reset the score. This simple Euler integration will simulate falling and landing, and that's all it will need to have for now.

```c
       
        vel_y += GRAVITY;
        player_y += vel_y;
        if (player_y >= HEIGHT - 50) {
            player_y = HEIGHT - 50;
            vel_y = 0;
            on_ground = -1;
        } else {
            on_ground = 0;
        }
        if (player_y > HEIGHT) {
            player_y = HEIGHT / 2;
            vel_y = 0;
            score = 0;
        }
        score++;
```

##### Rendering the Scene

Rendering clears the screen to black, draws a filled red 50x50 rectangle for the player at its position (cast to ints), then draws a blue line for the ground at the bottom. Finally, `SDL_RenderPresent` flips the buffers to display it. This double-buffered approach prevents tearing. The score increments each frame, accumulating as survival time.

This renders everything and includes the player at the position designated above. Additionally, it includes code to prevent tearing, called double-buffered rendering, which will help us always, regardless of what we do with the rest of the code.

```c
        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        // Draw player
        SDL_Rect player_rect = { (int)player_x, (int)player_y, 50, 50};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &player_rect);
        // Draw ground
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderDrawLine(renderer, 0, HEIGHT - 1, WIDTH, HEIGHT - 1);
        SDL_RenderPresent(renderer);
        // Delay for ~60 FPS
        SDL_Delay(16);
    }
```

##### Cleanup and Exit

Now that we are done writing the code, all that is left is to clean it up in code with `SDL_DestroyRenderer` and `SDL_DestroyWindow`, which will simply remove the renderer and window from memory. This ensures your graphics app does not continue running in the background.

```c
    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("Final Score: %d\n", score);
    return 0;
}
```

##### Epilogue: Moving Forward Towards God and Our Father in Heaven

You've made it all. Now it is time to steer towards God and never come back to tutorial hell. Amen and selah, you won here by not seeing hell, lol. Amen and selah, go into the fray and send us to space with God by loving us up for free and for the monetary. Amen and selah, you won again.
