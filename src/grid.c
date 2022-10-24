#include "grid.h"
#include <assert.h>

void print_grid(grid_t grid)
{
    printf("Grid length: %d\n", grid.length);
    printf("Grid positions:\n");
    for (int i = 0; i < grid.length; i++)
    {
        for (int j = 0; j < grid.length; j++)
        {
            cell_t cell = grid.cells[i * grid.length + j];
            printf("| (%d/%d) ", cell.group_id, cell.agent_count);
        }
        printf("|\n");
    }
}

void init_grid(grid_t *grid)
{
    grid->size = grid->length * grid->length;
    for (int i = 0; i < grid->size; i++)
    {
        cell_t *cell = grid->cells + i;
        cell->group_id = -1;
        cell->agent_count = 0;
    }
}

cell_t *get_cell(grid_t *grid, position_t pos)
{
    return grid->cells + (grid->length * pos.y + pos.x);
}

void terminate_grid(grid_t *grid)
{
    for (int i = 0; i < grid->size; i++)
    {
        cell_t *cell = grid->cells + i;
    }
}