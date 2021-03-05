#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
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

    SDL_SetWindowTitle(window, "Labyrinth");

    SDL_bool quit = SDL_FALSE;
    solve = SDL_FALSE;
    generate = SDL_TRUE;

    initGrid();
    SDL_Thread *generatingThread;
    SDL_Thread *solvingThread;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_WaitEvent(&event) && !quit)
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_RIGHT:
                    if (generate)
                    {
                        initGrid();
                        generatingThread = SDL_CreateThread(mazeGeneration, "Generating", NULL);
                    }
                    generate = SDL_FALSE;
                    continue;
                case SDL_BUTTON_LEFT:
                    if (solve)
                        solvingThread = SDL_CreateThread(mazeSolving, "Solving", NULL);
                    solve = SDL_FALSE;
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

/* Initialize the grid */
void initGrid()
{
    SDL_SetRenderDrawColor(renderer, 22, 22, 22, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
    for (int x = 0; x < window_width; x += grid_cell_size)
        SDL_RenderDrawLine(renderer, x, 0, x, window_height);

    for (int y = 0; y < window_height; y += grid_cell_size)
        SDL_RenderDrawLine(renderer, 0, y, window_width, y);

    /***** Starting cell *****/
    SDL_Rect startingCell;
    startingCell.x = grid_cell_size / 4;
    startingCell.y = grid_cell_size / 4;
    startingCell.w = grid_cell_size / 2;
    startingCell.h = grid_cell_size / 2;

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &startingCell);
    SDL_RenderDrawRect(renderer, &startingCell);

    /***** Terminal cell *****/
    SDL_Rect terminalCell;
    terminalCell.x = ((grid_width - 1) * grid_cell_size) + grid_cell_size / 4;
    terminalCell.y = ((grid_height - 1) * grid_cell_size) + grid_cell_size / 4;
    terminalCell.w = grid_cell_size / 2;
    terminalCell.h = grid_cell_size / 2;

    SDL_RenderFillRect(renderer, &terminalCell);
    SDL_RenderDrawRect(renderer, &terminalCell);
    SDL_RenderPresent(renderer);
}