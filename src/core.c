#include "core.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#ifdef DEBUG
void debug_timestamp()
{
    struct timespec ts;
    long msec;
    int err = clock_gettime(CLOCK_REALTIME, &ts);
    if (err)
    {
        perror("clock_gettime");
        exit(-1);
    }

    // round nanoseconds to milliseconds
    if (ts.tv_nsec >= 999500000)
    {
        ts.tv_sec++;
        msec = 0;
    }
    else
    {
        msec = (ts.tv_nsec + 500000) / 1000000;
    }

    struct tm *ptm = localtime(&ts.tv_sec);
    if (ptm == NULL)
    {
        perror("localtime");
        exit(-1);
    }

    char time_str[sizeof("23:59:59")];
    time_str[strftime(time_str, sizeof(time_str),
                      "%H:%M:%S", ptm)] = '\0';

    printf("[%s.%03li][DEBUG] ", time_str, msec);
}
#endif