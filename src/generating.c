#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "header.h"

/* Global variables */
static stack *firstCell;
SDL_bool visited[grid_width + 2][grid_height + 2];

void initMaze()
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

    for (int i = 1; i <= grid_width; i++)
        for (int j = 1; j <= grid_height; j++)
            visited[i][j] = SDL_FALSE;
    for (int j = 0; j < grid_height + 2; j++)
    {
        visited[0][j] = SDL_TRUE;
        visited[grid_width + 1][j] = SDL_TRUE;
    }
    for (int i = 1; i <= grid_width; i++)
    {
        visited[i][0] = SDL_TRUE;
        visited[i][grid_height + 1] = SDL_TRUE;
    }
    for (int i = 0; i < nbOfCells; i++)
        for (int j = 0; j < nbOfCells; j++)
            adjacencyMatrix[i][j] = SDL_FALSE;

    firstCell = NULL;
    srand(time(NULL));
}

void mazeGeneration()
{
    initMaze();

    cell *Cell = Malloc(cell);
    Cell->posX = 1;
    Cell->posY = 1;

    visited[Cell->posX][Cell->posY] = SDL_TRUE;
    push_stack(Cell);
    while (firstCell != NULL)
    {
        Cell = pop_stack();
        if (cellNeighbour(Cell) != NULL)
        {
            push_stack(Cell);
            cell *neighbour = cellNeighbour(Cell);
            removeWall(Cell, neighbour);
            visited[neighbour->posX][neighbour->posY] = SDL_TRUE;
            adjacency(Cell, neighbour);
            push_stack(neighbour);
        }
    }
}

void push_stack(cell *Cell)
{
    stack *newCell = Malloc(stack);
    newCell->Cell = Cell;
    newCell->next = firstCell;
    firstCell = newCell;
}

cell *pop_stack()
{
    cell *removedCell = firstCell->Cell;
    stack *p = firstCell;
    firstCell = firstCell->next;
    free(p);
    return removedCell;
}

cell *cellNeighbour(cell *Cell)
{
    cell *neighbour = Malloc(cell);
    cell *nullCell = NULL;

    if ((visited[Cell->posX - 1][Cell->posY] == SDL_TRUE) &&
        (visited[Cell->posX][Cell->posY - 1] == SDL_TRUE) &&
        (visited[Cell->posX][Cell->posY + 1] == SDL_TRUE) &&
        (visited[Cell->posX + 1][Cell->posY] == SDL_TRUE))
        return nullCell;

    do
    {
        int randomNeighbour = (rand() % 4) + 1;
        switch (randomNeighbour)
        {
        case 1:
            neighbour->posX = Cell->posX - 1;
            neighbour->posY = Cell->posY;
            break;
        case 2:
            neighbour->posX = Cell->posX;
            neighbour->posY = Cell->posY - 1;
            break;
        case 3:
            neighbour->posX = Cell->posX;
            neighbour->posY = Cell->posY + 1;
            break;
        case 4:
            neighbour->posX = Cell->posX + 1;
            neighbour->posY = Cell->posY;
            break;
        }
    } while (visited[neighbour->posX][neighbour->posY] == SDL_TRUE);

    return neighbour;
}

void removeWall(cell *Cell, cell *neighbour)
{
    if (Cell->posX == neighbour->posX)
    {
        SDL_SetRenderDrawColor(renderer, 22, 22, 22, 255);
        int posY = Max(Cell->posY, neighbour->posY);
        SDL_RenderDrawLine(renderer, (Cell->posX - 1) * grid_cell_size,
                           (posY - 1) * grid_cell_size,
                           (Cell->posX - 1) * grid_cell_size + grid_cell_size,
                           (posY - 1) * grid_cell_size);
    }

    else if (Cell->posY == neighbour->posY)
    {
        SDL_SetRenderDrawColor(renderer, 22, 22, 22, 255);
        int posX = Max(Cell->posX, neighbour->posX);
        SDL_RenderDrawLine(renderer, (posX - 1) * grid_cell_size,
                           (Cell->posY - 1) * grid_cell_size,
                           (posX - 1) * grid_cell_size,
                           (Cell->posY - 1) * grid_cell_size + grid_cell_size);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(30);
}