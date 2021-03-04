#include <SDL2/SDL.h>
#include "header.h"

/* Global varibales */
SDL_Renderer *renderer;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        exit(EXIT_FAILURE);

    SDL_Window *window;
    if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer) != 0)
        exit(EXIT_FAILURE);

    SDL_SetWindowTitle(window, "Maze generator");

    SDL_bool quit = SDL_FALSE;

    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_RIGHT:
                    mazeGeneration();
                    continue;
                case SDL_BUTTON_LEFT:
                    mazeSolving();
                    continue;
                }
            case SDL_QUIT:
                quit = SDL_TRUE;
                break;
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    exit(EXIT_SUCCESS);
}