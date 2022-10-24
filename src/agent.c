#include "agent.h"

void passa_tempo(int tid, int decimos)
{
    struct timespec zzz;

    zzz.tv_sec = decimos / 10;
    zzz.tv_nsec = (decimos % 10) * 100L * 1000000L;

    printf("PTa(%d,%d)\n", tid, decimos);
    nanosleep(&zzz, NULL);
    printf("PTb(%d,%d)\n", tid, decimos);
}

void print_agent(agent_t agent)
{
    printf("Agent [%d:%d]:\n\tPath length: %d\n\tPath:\n", agent.id, agent.group_id, agent.path_length);
    for (int i = 0; i < agent.path_length; i++)
        printf("\t\t(%d, %d, %d s)\n", agent.path[i].position.x, agent.path[i].position.y, agent.path[i].sleep_time);
}

// This is the funtion that wil be running on each thread
void *agent_run(void *arguments)
{
    agent_t *agent = (agent_t *)arguments;
    DEBUG_LOG("Agent %d started succesfully!\n", agent->id);
    passa_tempo(agent->id, agent->path[0].sleep_time);
    DEBUG_LOG("Agent %d finished succesfully!\n", agent->id);
}