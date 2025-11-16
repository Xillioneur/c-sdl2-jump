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