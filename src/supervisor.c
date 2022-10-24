#include "supervisor.h"
#include <assert.h>
#include <pthread.h>
#include <time.h>

void enter_cell(agent_t *agent, cell_t *cell_to_enter)
{
    pthread_mutex_lock(&(cell_to_enter->mutex));
    DEBUG_LOG("%d:\t Mutex acquired\n", agent->id)
    while (cell_to_enter->group_id != agent->group_id && cell_to_enter->group_id > 0)
    {
        DEBUG_LOG("%d:\t Waiting to enter\n", agent->id);
        pthread_cond_wait(&(cell_to_enter->empty), &(cell_to_enter->mutex));
    }

    cell_to_enter->agent_count++;
    if (cell_to_enter->agent_count == 1)
        cell_to_enter->group_id = agent->group_id;

    pthread_mutex_unlock(&(cell_to_enter->mutex));
    pthread_cond_broadcast(&(cell_to_enter->occupied));
    DEBUG_LOG("%d:\t Mutex released\n", agent->id)
}

void leave_cell(agent_t *agent, cell_t *cell_to_leave)
{
    pthread_mutex_lock(&(cell_to_leave->mutex));
    DEBUG_LOG("%d:\t Mutex acquired\n", agent->id)

    cell_to_leave->agent_count--;
    if (cell_to_leave->agent_count == 0)
    {
        cell_to_leave->group_id = -1;
        pthread_cond_broadcast(&(cell_to_leave->empty));
    }
    pthread_mutex_unlock(&(cell_to_leave->mutex));
    DEBUG_LOG("%d:\t Mutex released\n", agent->id)
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

    DEBUG_LOG("%d: begin 0\n", agent->id);
    step_t initial_step = agent->path[0];
    enter_cell(agent, get_cell(agent->grid, initial_step.position));
    passa_tempo(agent->id, initial_step.sleep_time);
    agent->current_step_id++;
    DEBUG_LOG("%d: finished 0\n", agent->id);

    while (agent->current_step_id < agent->path_length)
    {
        step_t current_step = agent->path[agent->current_step_id];
        step_t previous_step = agent->path[agent->current_step_id - 1];

        DEBUG_LOG("%d: begin step %d (%d, %d) -> (%d, %d)\n", agent->id, agent->current_step_id, previous_step.position.x, previous_step.position.y, current_step.position.x, current_step.position.y);

        // Enter cell of current step
        enter_cell(agent, get_cell(agent->grid, current_step.position));
        DEBUG_LOG("%d:\t entered (%d, %d)\n", agent->id, current_step.position.x, current_step.position.y);

        // Leave cell of previous step
        leave_cell(agent, get_cell(agent->grid, previous_step.position));
        DEBUG_LOG("%d:\t left (%d, %d)\n", agent->id, previous_step.position.x, previous_step.position.y);

        passa_tempo(agent->id, current_step.sleep_time);

        DEBUG_LOG("%d: finished %d\n", agent->id, agent->current_step_id);
        agent->current_step_id++;
    }

    DEBUG_LOG("%d: finished succesfully!\n", agent->id);
}