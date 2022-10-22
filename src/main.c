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

void print_state(grid_t *g, supervisor_t *s)
{
    print_agents(s);
    print_grid(g);
}

int main(int argc, char const *argv[])
{
    grid_t grid;
    supervisor_t supervisor;

    // Process input and initialize data structures
    FILE *input_file = open_file("tests/test.txt", READ_MODE);

    int buffer[128];

    // Get grid size and number of agents
    fscanf(input_file, "%d %d", &grid.length, &supervisor.num_agents);
    print_state(&grid, &supervisor);

    supervisor.agents = (agent_t *)malloc(supervisor.num_agents * sizeof(agent_t));

    for (int i = 0; i < supervisor.num_agents; i++)
    {
        agent_t *agent = &supervisor.agents[0];
        fscanf(input_file, "%d %d %d", &agent->id, &agent->group_id, &agent->path_length);
        for (int j=0; j<agent->path_length; j++)
        {
            step_t step;
            fscanf(input_file, "%d %d %d", &step.position.x, &step.position.y, &step.sleep_time);
            agent->path[j] = step;
        }
        print_agent(agent);
    }

    close_file(input_file);

    return 0;
}
