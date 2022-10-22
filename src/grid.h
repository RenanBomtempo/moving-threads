#ifndef GRID_h
#define GRID_h

#include <stdlib.h>
#include <stdio.h>
#include "core.h"
#include "position.h"


typedef struct grid_t
{
    int length; // Number of positions in each line/column of the grid
    int positions[MAX_GRID_LENGTH * MAX_GRID_LENGTH];
} grid_t;

void initialize_grid(grid_t *grid, int length);

void move(grid_t *grid, position_t from, position_t to);

void print_grid(grid_t *grid);

#endif