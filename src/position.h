#ifndef POSITION_H
#define POSITION_H

typedef struct position_t
{
    int x;
    int y;
} position_t;

position_t out_of_grid_position();

#endif