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

int main(int argc, char const *argv[])
{
    grid_t grid;
    supervisor_t supervisor;

    input_processing("tests/test.txt", &grid, &supervisor);

    init_grid(&grid);
    init_agents(&supervisor);

    terminate_agents(&supervisor);

    return 0;
}
