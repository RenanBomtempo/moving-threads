#include "input.h"
#include <assert.h>

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
    DEBUG_LOG("File closed successfuly!\n");
}

/* Read the input file and store data in grid and supervisor data structures.
 */
void input_processing(const char *filename, grid_t *grid, supervisor_t *supervisor)
{
    // Process input and initialize data structures
    FILE *input_file = open_file(filename, READ_MODE);

    // Get grid size and number of agents
    assert(fscanf(input_file, "%d %d", &grid->length, &supervisor->num_agents));

    // Read agents data
    for (int i = 0; i < supervisor->num_agents; i++)
    {
        agent_t *agent = &supervisor->agents[i];
        assert(fscanf(input_file, "%d %d %d", &agent->id, &agent->group_id, &agent->path_length));
        for (int j = 0; j < agent->path_length; j++)
        {
            step_t step;
            assert(fscanf(input_file, "%d %d %d", &step.position.x, &step.position.y, &step.sleep_time));
            agent->path[j] = step;
        }
        agent->current_step_id = 0;
        agent->grid = grid;
    }

    close_file(input_file);
}