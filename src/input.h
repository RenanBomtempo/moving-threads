#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>
#include <stdio.h>
#include "core.h"
#include "supervisor.h"
#include "grid.h"

#define READ_MODE "r"
#define WRITE_MODE "w"

typedef struct Input
{
    int grid_length;
    int num_agents;

} Input;

FILE *open_file(const char *filename, const char *mode);

void close_file(FILE *file);

void input_processing(const char *filename, grid_t *grid, supervisor_t *supervisor);

#endif