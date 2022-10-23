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

void print_agent(agent_t a)
{
#ifdef DEBUG
    printf("Agent [%d:%d]:\n\tPath length: %d\n\tPath:\n", a.id, a.group_id, a.path_length);
    for (int i = 0; i < a.path_length; i++)
    {
        printf("\t\t(%d, %d, %d s)\n", a.path[i].position.x, a.path[i].position.y, a.path[i].sleep_time);
    }
#endif
}