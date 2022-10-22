#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>
#include <stdio.h>
#include "core.h"
#include "grid.h"
#include "agent.h"

#define READ_MODE "r"
#define WRITE_MODE "w"

typedef struct Input
{
    int grid_length;
    int num_agents;

} Input;

FILE *open_file(const char *filename, const char *mode);

void close_file(FILE *file);

#endif