#include "agent.h"

void print_agent(agent_t agent)
{
    printf("Agent [%d:%d]:\n\tPath length: %d\n\tPath:\n", agent.id, agent.group_id, agent.path_length);
    for (int i = 0; i < agent.path_length; i++)
        printf("\t\t(%d, %d, %d s)\n", agent.path[i].position.x, agent.path[i].position.y, agent.path[i].sleep_time);
}

void passa_tempo(int tid, int decimos)
{
    struct timespec zzz;

    zzz.tv_sec = decimos / 10;
    zzz.tv_nsec = (decimos % 10) * 100L * 1000000L;

    printf("PTa(%d,%d)\n", tid, decimos);
    nanosleep(&zzz, NULL);
    printf("PTb(%d,%d)\n", tid, decimos);
}
