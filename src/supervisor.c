#include "supervisor.h"
#include <assert.h>
#include <pthread.h>

void print_agents(supervisor_t *supervisor)
{
    printf("Number of agents: %d\n", supervisor->num_agents);
    for (int i = 0; i < supervisor->num_agents; i++)
        print_agent(supervisor->agents[i]);
}

void init_agents(supervisor_t *supervisor)
{
    for (int i = 0; i < supervisor->num_agents; i++)
    {
        agent_t *agent = &supervisor->agents[i];
        assert(!pthread_create(&supervisor->agents[i].thread, NULL, agent_run, agent));
    }
    DEBUG_LOG("All agent threads were created succesfully!\n");
}

void terminate_agents(supervisor_t *supervisor)
{
    for (int i = 0; i < supervisor->num_agents; i++)
        assert(!pthread_join(supervisor->agents[i].thread, NULL));

    DEBUG_LOG("All agent threads were joined succesfully!\n");
}