#include "philo.h"

bool exceed_time_to_die(t_data *data)
{
    int i;
    long last_time_eat;

    if (is_sim_end(data))
        return (true);
    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_lock(&data->meals_lock);
        last_time_eat = data->philo[i].last_time_eat;
        pthread_mutex_unlock(&data->meals_lock);
        if (get_time_in__ms() - last_time_eat > data->time_to_die)
        {
            print_state(&data->philo[i], "died");
            pthread_mutex_lock(&data->death_lock);
            data->sim_end = true;
            pthread_mutex_unlock(&data->death_lock);
            return (true);
        }
        i++;
    }
    return (false);
}

bool all_eat_enough(t_data *data)
{
    int i;
    int full_philos;

    if (is_sim_end(data))
        return (true);
    i = 0;
    pthread_mutex_lock(&data->meals_lock);
    full_philos = data->full_philos;
    pthread_mutex_unlock(&data->meals_lock);
    if (full_philos == data->num_philos)
    {
        pthread_mutex_lock(&data->death_lock);
        data->sim_end = 1;
        pthread_mutex_unlock(&data->death_lock);
        return true;
    }
    return (false);
}
int ft_sleep(long mill, t_data *data)
{
    long start;

    start = get_time_in__ms();
    while ((get_time_in__ms() - start) < mill)
    {
        // if (is_sim_end(data))
        //     return (-1);
        usleep(200);
    }
    return (0);
}
