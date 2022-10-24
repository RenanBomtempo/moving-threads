#include "grid.h"

void move(grid_t *grid, position_t from, position_t to)
{
}

void print_grid(grid_t *grid)
{
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
}

void init_grid(grid_t *grid)
{
    grid->size = grid->length * grid->length;
    for (int i = 0; i < grid->size; i++)
        grid->cells[i] = -1;
}

void set_cell_value(grid_t *grid, position_t pos, int value)
{
    grid->cells[calculate_position_index(pos)] = value;
}