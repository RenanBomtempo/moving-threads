#ifndef GRID_h
#define GRID_h

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "core.h"
#include "position.h"

typedef struct cell_t
{
    int group_id;    // ID of the agent's group
    int agent_count; // Number of agents in the cell
} cell_t;

typedef struct grid_t
{
    int length; // Number of positions in each line/column of the grid
    int size;
    cell_t cells[MAX_GRID_LENGTH * MAX_GRID_LENGTH];
} grid_t;

cell_t *get_cell(grid_t *grid, position_t pos);
void print_grid(grid_t grid);
void init_grid(grid_t *grid);
void terminate_grid(grid_t *grid);

#endif