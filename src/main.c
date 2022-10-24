// =============================================================================
// Descrição:   Arquivo main do programa moving-threads. Primeio trabalho
//              prático da disciplina de Fundamentos de Sistemas Paralelos
//              e Distribuidos.
// Author:  Renan Bomtempo
// =============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "input.h"
#include "grid.h"
#include "supervisor.h"

#ifdef DEBUG
#define DEBUG_GRID(g) print_grid(g);
#else
#define DEBUG_GRID(g)
#endif

int main(int argc, char const *argv[])
{
    grid_t grid;
    supervisor_t supervisor;

    input_processing("tests/test3.txt", &grid, &supervisor);

    init_grid(&grid);
    init_agents(&supervisor);
    DEBUG_GRID(grid);

    terminate_agents(&supervisor);
    DEBUG_GRID(grid);

    terminate_grid(&grid);

    return 0;
}
