#include "supervisor.h"
#include <assert.h>
#include <pthread.h>

void enter_cell(grid_t *grid, agent_t *agent)
{
    step_t current_step = agent->path[agent->current_step_id];
    cell_t *cell_to_enter = get_cell(grid, current_step.position);

    cell_to_enter->agent_count++;
    if (cell_to_enter->agent_count == 1)
        cell_to_enter->group_id = agent->group_id;

    agent->position = current_step.position;
}

void leave_cell(grid_t *grid, agent_t *agent)
{
    step_t current_step = agent->path[agent->current_step_id];
    cell_t *cell_to_leave = get_cell(grid, current_step.position);

    cell_to_leave->agent_count--;
    if (cell_to_leave->agent_count == 0)
        cell_to_leave->group_id = -1;

    agent->position = out_of_grid_position();
    agent->current_step_id++;
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
    DEBUG_LOG("Agent %d started succesfully!\n", agent->id);

    enter_cell(grid, agent);
    passa_tempo(agent->id, agent->path[agent->current_step_id].sleep_time);

    //    while (agent->current_step_id <= agent->path_length)
    //    {
    leave_cell(grid, agent);
    enter_cell(grid, agent);
    passa_tempo(agent->id, agent->path[agent->current_step_id].sleep_time);
    //}

    DEBUG_LOG("Agent %d finished succesfully!\n", agent->id);
}