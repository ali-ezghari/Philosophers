#include "philo.h"

void destroy_free(t_data *data, bool destroy_write_lock)
{
    if (destroy_write_lock)
    {
        if (pthread_mutex_destroy(&data->write_lock) != 0)
        {
            mutex_destroy_err();
        }
    }
    free(data->philo);
}

void clean_forks_array(t_data *data, int i)
{
    int j;

    j = 0;
    while (j < i)
    {
        if (pthread_mutex_destroy(&data->forks[j]) != 0)
            mutex_destroy_err();
        j++;
    }
    free(data->forks);
    destroy_free(data, true);
}

void destroy_free_all(t_data *data)
{
    clean_forks_array(data, data->num_philos);
    free(data);
}