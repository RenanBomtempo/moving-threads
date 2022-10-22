#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "input.h"

void passa_tempo(int tid, int decimos)
{
    struct timespec zzz;

    zzz.tv_sec = decimos / 10;
    zzz.tv_nsec = (decimos % 10) * 100L * 1000000L;

    printf("PTa(%d,%d)\n", tid, decimos);
    nanosleep(&zzz, NULL);
    printf("PTb(%d,%d)\n", tid, decimos);
}

int main(int argc, char const *argv[])
{
    FILE *file = open_file("tests/test.txt");

    close_file(file);

    return 0;
}
