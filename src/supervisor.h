#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "agent.h"

typedef struct supervisor_t
{
    int num_agents;
    agent_t agents[MAX_PATH_LENGTH];
} supervisor_t;

void print_agents(supervisor_t *supervisor);
void init_agents(supervisor_t *supervisor);
void terminate_agents(supervisor_t *supervisor);
void *agent_run(void *arguments);
void enter_cell(grid_t *grid, agent_t *agent);
void leave_cell(grid_t *grid, agent_t *agent);

#endif