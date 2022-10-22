#include "supervisor.h"

void print_agents(supervisor_t *s)
{
#ifdef DEBUG
    printf("Number of agents: %d\n", s->num_agents);
#endif
}