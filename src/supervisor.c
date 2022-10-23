#include "supervisor.h"

void print_agents(supervisor_t *s)
{
#ifdef DEBUG
    printf("Number of agents: %d\n", s->num_agents);
    for (int i = 0; i < s->num_agents; i++)
        print_agent(s->agents[i]);
#endif
}