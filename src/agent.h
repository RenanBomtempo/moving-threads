#ifndef AGENT_H
#define AGENT_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "core.h"
#include "position.h"
#include "grid.h"

typedef struct step_t
{
    int sleep_time;
    position_t position;
} step_t;

typedef struct agent_t
{
    int id;
    int group_id;
    int path_length;
    int current_step_id;
    pthread_t thread;
    position_t position;
    step_t path[MAX_PATH_LENGTH];
    grid_t *grid;
} agent_t;

void print_agent(agent_t a);
void passa_tempo(int tid, int decimos);

#endif