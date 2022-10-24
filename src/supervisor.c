#include "supervisor.h"
#include <assert.h>
#include <pthread.h>
#include <time.h>

void enter_cell(grid_t *grid, agent_t *agent)
{
    step_t current_step = agent->path[agent->current_step_id];
    cell_t *cell_to_enter = get_cell(grid, current_step.position);

    pthread_mutex_lock(&(cell_to_enter->mutex));
    DEBUG_LOG("%d: Mutex acquired (%d, %d)\n", agent->id, current_step.position.x, current_step.position.y)
    while (cell_to_enter->group_id != agent->group_id && cell_to_enter->group_id > 0)
    {
        DEBUG_LOG("%d:\t Waiting to enter\n", agent->id);
        pthread_cond_wait(&(cell_to_enter->empty), &(cell_to_enter->mutex));
    }

    cell_to_enter->agent_count++;
    if (cell_to_enter->agent_count == 1)
        cell_to_enter->group_id = agent->group_id;

    pthread_cond_signal(&(cell_to_enter->occupied));
    pthread_mutex_unlock(&(cell_to_enter->mutex));

    agent->position = current_step.position;
    DEBUG_LOG("%d: Entered position (%d, %d)\n", agent->id, current_step.position.x, current_step.position.y)
}

void leave_cell(grid_t *grid, agent_t *agent)
{
    step_t current_step = agent->path[agent->current_step_id];
    cell_t *cell_to_leave = get_cell(grid, current_step.position);

    pthread_mutex_lock(&(cell_to_leave->mutex));
    DEBUG_LOG("%d: Mutex acquired (%d, %d)\n", agent->id, current_step.position.x, current_step.position.y)

    cell_to_leave->agent_count--;
    if (cell_to_leave->agent_count == 0)
    {
        cell_to_leave->group_id = -1;
        pthread_cond_signal(&(cell_to_leave->empty));
    }
    pthread_mutex_unlock(&(cell_to_leave->mutex));

    agent->position = out_of_grid_position();
    DEBUG_LOG("%d: Left position (%d, %d)\n", agent->id, current_step.position.x, current_step.position.y)
}

void print_agents(supervisor_t *supervisor)
{
    printf("Number of agents: %d\n", supervisor->num_agents);
    for (int i = 0; i < supervisor->num_agents; i++)
        print_agent(supervisor->agents[i]);
}

void init_agents(supervisor_t *supervisor)
{
    for (int i = 0; i < supervisor->num_agents; i++)
    {
        agent_t *agent = supervisor->agents + i;
        assert(!pthread_create(&supervisor->agents[i].thread, NULL, agent_run, agent));
    }
    DEBUG_LOG("All agent threads were created succesfully!\n");
}

void terminate_agents(supervisor_t *supervisor)
{
    for (int i = 0; i < supervisor->num_agents; i++)
        assert(!pthread_join(supervisor->agents[i].thread, NULL));

    DEBUG_LOG("All agent threads were joined succesfully!\n");
}

// This is the funtion that wil be running on each thread
void *agent_run(void *arguments)
{
    agent_t *agent = (agent_t *)arguments;
    grid_t *grid = agent->grid;
    DEBUG_LOG("%d: started succesfully!\n", agent->id);

    while (agent->current_step_id < agent->path_length)
    {
        DEBUG_LOG("%d: begin %d\n", agent->id, agent->current_step_id);

        enter_cell(grid, agent);
        passa_tempo(agent->id, agent->path[agent->current_step_id].sleep_time);

        // Leave only if this is not the last step
        if (agent->current_step_id + 1 < agent->path_length)
            leave_cell(grid, agent);

        DEBUG_LOG("%d: finished %d\n", agent->id, agent->current_step_id);
        agent->current_step_id++;
    }

    DEBUG_LOG("%d: finished succesfully!\n", agent->id);
}