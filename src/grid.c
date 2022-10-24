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
        assert(!pthread_mutex_init(&(cell->mutex), NULL));
        assert(!pthread_cond_init(&(cell->occupied), NULL));
        assert(!pthread_cond_init(&(cell->empty), NULL));
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
        pthread_mutex_destroy(&(cell->mutex));
        pthread_cond_destroy(&(cell->occupied));
        pthread_cond_destroy(&(cell->empty));
    }
}