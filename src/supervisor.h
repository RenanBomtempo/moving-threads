#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "agent.h"

typedef struct supervisor_t
{
    int num_agents;
    agent_t *agents;
} supervisor_t;

void print_agents(supervisor_t *s);

#endif