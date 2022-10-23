#include "grid.h"

void initialize_grid(grid_t *grid, int length)
{
    grid->length = length;
}

void move(grid_t *grid, position_t from, position_t to)
{
}

void print_grid(grid_t *grid)
{
#ifdef DEBUG
    printf("Grid length: %d\n", grid->length);
    printf("Grid positions:\n");
    for (int i = 0; i < grid->length; i++)
    {
        for (int j = 0; j < grid->length; j++)
        {
            printf("| %d ", grid->cells[i * j]);
        }
        printf("|\n");
    }
#endif
}