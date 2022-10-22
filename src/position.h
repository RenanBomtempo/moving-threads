#ifndef POSITION_H
#define POSITION_H

typedef struct position_t
{
    int x;
    int y;
} position_t;

int calculate_position_index(position_t p);

#endif