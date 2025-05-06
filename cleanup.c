#include "philo.h"

void destroy_free(t_data *data, int count)
{
    free(data->philo);
    if (count == 1)
    {
        if (pthread_mutex_destroy(&data->meals_lock) != 0)
            mutex_destroy_err();
    }
    else if (count == 2)
    {
        if (pthread_mutex_destroy(&data->meals_lock) != 0)
            mutex_destroy_err();
        if (pthread_mutex_destroy(&data->write_lock) != 0)
            mutex_destroy_err();
    }
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