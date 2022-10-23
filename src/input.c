#include "input.h"

FILE *open_file(const char *filename, const char *mode)
{
    FILE *file_ptr = fopen(filename, mode);

    if (!file_ptr)
    {
        printf("Could not open file.\n");
        exit(-1);
    }

    DEBUG_LOG("File opened succesfully!\n");

    return file_ptr;
}

void close_file(FILE *file)
{
    fclose(file);
}

void input_processing(const char *filename, grid_t *grid, supervisor_t *supervisor)
{
    // Process input and initialize data structures
    FILE *input_file = open_file("tests/test.txt", READ_MODE);

    // Get grid size and number of agents
    fscanf(input_file, "%d %d", &grid->length, &supervisor->num_agents);
    print_grid(grid);

    // Read agents data
    supervisor->agents = (agent_t *)malloc(supervisor->num_agents * sizeof(agent_t));
    for (int i = 0; i < supervisor->num_agents; i++)
    {
        agent_t *agent = &supervisor->agents[i];
        fscanf(input_file, "%d %d %d", &agent->id, &agent->group_id, &agent->path_length);
        for (int j = 0; j < agent->path_length; j++)
        {
            step_t step;
            fscanf(input_file, "%d %d %d", &step.position.x, &step.position.y, &step.sleep_time);
            agent->path[j] = step;
        }
    }
    print_agents(supervisor);

    close_file(input_file);
}