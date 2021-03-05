#include <stdlib.h>
#include <SDL2/SDL.h>
#include "header.h"

/* Global variables */
static queue *firstCell;
SDL_bool adjacencyMatrix[nbOfCells][nbOfCells];
cell *parent[grid_width][grid_height];

void initBFS()
{
    firstCell = NULL;
    for (int i = 0; i < grid_width; i++)
        for (int j = 0; j < grid_height; j++)
        {
            parent[i][j] = NULL;
            visited[i + 1][j + 1] = SDL_FALSE;
        }
    visited[1][1] = SDL_TRUE;
}

int mazeSolving(void *ptr)
{
    generate = SDL_FALSE;
    solve = SDL_FALSE;
    initBFS();
    cell *Cell = Malloc(cell);
    Cell->posX = 1;
    Cell->posY = 1;
    enqueue(Cell);
    while (visited[grid_width][grid_height] == SDL_FALSE)
    {
        cell *Cell = dequeue();
        queueCellNeighbours(Cell);
    }
    shortPath();
    solve = SDL_TRUE;
    generate = SDL_TRUE;
}

void queueCellNeighbours(cell *Cell)
{
    SDL_SetRenderDrawColor(renderer, 100, 0, 0, 0);
    SDL_Rect rectCell;
    if (!((Cell->posX == 1) && (Cell->posY == 1)))
    {
        rectCell.x = ((Cell->posX - 1) * grid_cell_size) + 3 * grid_cell_size / 8;
        rectCell.y = ((Cell->posY - 1) * grid_cell_size) + 3 * grid_cell_size / 8;
        rectCell.w = grid_cell_size / 4;
        rectCell.h = grid_cell_size / 4;
        SDL_RenderFillRect(renderer, &rectCell);
        SDL_RenderDrawRect(renderer, &rectCell);
    }

    cell *neighbourCell;
    neighbourCell = Malloc(cell);
    neighbourCell->posX = Cell->posX - 1;
    neighbourCell->posY = Cell->posY;
    if ((visited[neighbourCell->posX][neighbourCell->posY] == SDL_FALSE) && (isAdjacency(Cell, neighbourCell) == SDL_TRUE))
    {
        visited[neighbourCell->posX][neighbourCell->posY] = SDL_TRUE;
        parent[neighbourCell->posX - 1][neighbourCell->posY - 1] = Cell;
        enqueue(neighbourCell);

        rectCell.x = ((Cell->posX - 1) * grid_cell_size) - 3 * grid_cell_size / 8;
        rectCell.y = ((neighbourCell->posY - 1) * grid_cell_size) + 3 * grid_cell_size / 8;
        rectCell.w = grid_cell_size;
        rectCell.h = grid_cell_size / 4;
        SDL_RenderFillRect(renderer, &rectCell);
        SDL_RenderDrawRect(renderer, &rectCell);
    }

    neighbourCell = Malloc(cell);
    neighbourCell->posX = Cell->posX;
    neighbourCell->posY = Cell->posY - 1;
    if ((visited[neighbourCell->posX][neighbourCell->posY] == SDL_FALSE) && (isAdjacency(Cell, neighbourCell) == SDL_TRUE))
    {
        visited[neighbourCell->posX][neighbourCell->posY] = SDL_TRUE;
        parent[neighbourCell->posX - 1][neighbourCell->posY - 1] = Cell;
        enqueue(neighbourCell);

        rectCell.x = ((neighbourCell->posX - 1) * grid_cell_size) + 3 * grid_cell_size / 8;
        rectCell.y = ((Cell->posY - 1) * grid_cell_size) - 3 * grid_cell_size / 8;
        rectCell.w = grid_cell_size / 4;
        rectCell.h = grid_cell_size;
        SDL_RenderFillRect(renderer, &rectCell);
        SDL_RenderDrawRect(renderer, &rectCell);
    }

    neighbourCell = Malloc(cell);
    neighbourCell->posX = Cell->posX;
    neighbourCell->posY = Cell->posY + 1;
    if ((visited[neighbourCell->posX][neighbourCell->posY] == SDL_FALSE) && (isAdjacency(Cell, neighbourCell) == SDL_TRUE))
    {
        visited[neighbourCell->posX][neighbourCell->posY] = SDL_TRUE;
        parent[neighbourCell->posX - 1][neighbourCell->posY - 1] = Cell;
        enqueue(neighbourCell);

        rectCell.x = ((neighbourCell->posX - 1) * grid_cell_size) + 3 * grid_cell_size / 8;
        rectCell.y = ((neighbourCell->posY - 1) * grid_cell_size) - 3 * grid_cell_size / 8;
        rectCell.w = grid_cell_size / 4;
        rectCell.h = grid_cell_size;
        SDL_RenderFillRect(renderer, &rectCell);
        SDL_RenderDrawRect(renderer, &rectCell);
    }

    neighbourCell = Malloc(cell);
    neighbourCell->posX = Cell->posX + 1;
    neighbourCell->posY = Cell->posY;
    if ((visited[neighbourCell->posX][neighbourCell->posY] == SDL_FALSE) && (isAdjacency(Cell, neighbourCell) == SDL_TRUE))
    {
        visited[neighbourCell->posX][neighbourCell->posY] = SDL_TRUE;
        parent[neighbourCell->posX - 1][neighbourCell->posY - 1] = Cell;
        enqueue(neighbourCell);

        rectCell.x = ((neighbourCell->posX - 1) * grid_cell_size) - 3 * grid_cell_size / 8;
        rectCell.y = ((neighbourCell->posY - 1) * grid_cell_size) + 3 * grid_cell_size / 8;
        rectCell.w = grid_cell_size;
        rectCell.h = grid_cell_size / 4;
        SDL_RenderFillRect(renderer, &rectCell);
        SDL_RenderDrawRect(renderer, &rectCell);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(30);
}

void shortPath()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_Rect rectCell;
    cell *Cell = Malloc(cell);
    cell *parentCell;
    Cell->posX = grid_width;
    Cell->posY = grid_height;
    while ((Cell->posX != 1) || (Cell->posY != 1))
    {
        rectCell.x = (Cell->posX * grid_cell_size) - 5 * grid_cell_size / 8;
        rectCell.y = ((Cell->posY - 1) * grid_cell_size) + 3 * grid_cell_size / 8;
        rectCell.w = grid_cell_size / 4;
        rectCell.h = grid_cell_size / 4;
        SDL_RenderFillRect(renderer, &rectCell);
        SDL_RenderDrawRect(renderer, &rectCell);
        parentCell = parent[Cell->posX - 1][Cell->posY - 1];
        if (Cell->posX == parentCell->posX)
        {
            int posY = Min(Cell->posY, parentCell->posY);
            rectCell.x = (Cell->posX * grid_cell_size) - 5 * grid_cell_size / 8;
            rectCell.y = ((posY - 1) * grid_cell_size) + 3 * grid_cell_size / 8;
            rectCell.w = grid_cell_size / 4;
            rectCell.h = grid_cell_size;
            SDL_RenderFillRect(renderer, &rectCell);
            SDL_RenderDrawRect(renderer, &rectCell);
        }
        else if (Cell->posY == parentCell->posY)
        {
            int posX = Min(Cell->posX, parentCell->posX);
            rectCell.x = (posX * grid_cell_size) - 3 * grid_cell_size / 8;
            rectCell.y = ((Cell->posY - 1) * grid_cell_size) + 3 * grid_cell_size / 8;
            rectCell.w = grid_cell_size;
            rectCell.h = grid_cell_size / 4;
            SDL_RenderFillRect(renderer, &rectCell);
            SDL_RenderDrawRect(renderer, &rectCell);
        }
        Cell = parentCell;
        SDL_Delay(10);
        SDL_RenderPresent(renderer);
    }
}

void enqueue(cell *Cell)
{
    queue *newCell = Malloc(queue);
    newCell->Cell = Cell;
    newCell->next = NULL;
    if (firstCell == NULL)
    {
        firstCell = newCell;
        return;
    }
    queue *p = firstCell;
    queue *predCell;
    while (p != NULL)
    {
        predCell = p;
        p = p->next;
    }
    predCell->next = newCell;
}

cell *dequeue()
{
    cell *removedCell = firstCell->Cell;
    queue *p = firstCell;
    firstCell = firstCell->next;
    free(p);
    return removedCell;
}

void adjacency(cell *Cell, cell *cellNeighbour)
{
    int cellPos = (Cell->posX - 1) * grid_height + (Cell->posY - 1);
    int neighbourPos = (cellNeighbour->posX - 1) * grid_height + (cellNeighbour->posY - 1);
    adjacencyMatrix[cellPos][neighbourPos] = SDL_TRUE;
    adjacencyMatrix[neighbourPos][cellPos] = SDL_TRUE;
}

SDL_bool isAdjacency(cell *Cell, cell *cellNeighbour)
{
    int cellPos = (Cell->posX - 1) * grid_height + (Cell->posY - 1);
    int neighbourPos = (cellNeighbour->posX - 1) * grid_height + (cellNeighbour->posY - 1);
    return adjacencyMatrix[cellPos][neighbourPos];
}