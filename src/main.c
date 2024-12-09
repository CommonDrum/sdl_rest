#include <SDL.h>

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Define vertices as a static array
    SDL_Vertex verts[] = {
        {
            .position = {400, 150},
            .color = {255, 0, 0, 255},
            .tex_coord = {0, 0}
        },
        {
            .position = {200, 450},
            .color = {0, 0, 255, 255},
            .tex_coord = {0, 0}
        },
        {
            .position = {600, 450},
            .color = {0, 255, 0, 255},
            .tex_coord = {0, 0}
        }
    };
    
    int num_verts = sizeof(verts) / sizeof(verts[0]);
    
    SDL_bool running = SDL_TRUE;
    while (running)
    {
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            if ((SDL_QUIT == ev.type) ||
                (SDL_KEYDOWN == ev.type && SDL_SCANCODE_ESCAPE == ev.key.keysym.scancode))
            {
                running = SDL_FALSE;
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderGeometry(renderer, NULL, verts, num_verts, NULL, 0);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
