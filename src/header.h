#ifndef HEAEDER
#define HEAEDER

#define Malloc(t) (t *)malloc(sizeof(t))
#define Max(a, b) (a > b) ? a : b
#define Min(a, b) (a < b) ? a : b

/* Define constantes */
#define grid_cell_size 40
#define grid_width 25
#define grid_height 15
#define window_width (grid_width * grid_cell_size) + 1
#define window_height (grid_height * grid_cell_size) + 1
#define nbOfCells (grid_width * grid_height)

/* Cell representaion */
typedef struct
{
    int posX;
    int posY;
} cell;

/* Stack representation */
typedef struct _stack
{
    cell *Cell;
    struct _stack *next;
} stack;

/* Queue representation */
typedef struct _queue
{
    cell *Cell;
    struct _queue *next;
} queue;

/* External global variables */
extern SDL_Renderer *renderer;
extern SDL_bool visited[grid_width + 2][grid_height + 2];
extern SDL_bool adjacencyMatrix[nbOfCells][nbOfCells];
extern SDL_bool generate;
extern SDL_bool solve;
extern SDL_bool firstLook;

/* Prototypes of functions */
/***** Initialize the grid *****/
void initGrid();
/***** Maze generation *****/
int mazeGeneration(void *ptr);
void push_stack(cell *Cell);
cell *pop_stack();
cell *cellNeighbour(cell *Cell);
void removeWall(cell *Cell, cell *neighbour);
/***** Maze solving *****/
void adjacency(cell *Cell, cell *cellNeighbour);
SDL_bool isAdjacency(cell *Cell, cell *cellNeighbour);
int mazeSolving(void *ptr);
void enqueue(cell *Cell);
cell *dequeue();
void queueCellNeighbours(cell *Cell);
void shortPath();

#endif