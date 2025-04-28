#include "philo.h"

int	ft_sleep(long mill)
{
	long start;

	start = get_time_in__ms();
	while ((get_time_in__ms() - start) < mill)
		usleep(500);
	return (0);
}

bool exceed_time_to_die(t_data *data)
{
    int i;
    long now;
    long last_time_eat;

    if (is_sim_end(data))
        return (true);
    i = 0;
    now = get_time_in__ms();
    while (i < data->num_philos)
    {
        pthread_mutex_lock(&data->death_lock);
        last_time_eat = data->philo[i].last_time_eat;
        pthread_mutex_unlock(&data->death_lock);
        if (now - last_time_eat > data->time_to_die)
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

// bool all_eat_enough(t_data *data)
// {
//     int i;
//     t_philo *philo;

//     if (is_sim_end(data))
//         return (true);
//     i = 0;
//     philo = data->philo;
//     while (i < data->num_philos)
//     {
//         if (is_sim_end(data))
//             return (true);
//         else if (check_meals(&philo[i]))
//             return false;
//         i++;
//     }
//     return (true);
// }

void join_philo_threads(t_data *data, int count)
{
    int i = 0;
    while (i < count)
    {
        if (pthread_join(data->philo[i].p_thread, NULL) != 0)
            printf("Failed to join thread %d\n", i);
        i++;
    }
}

bool check_meals(t_philo *philo)
{
    if (philo->meals_eaten != -1 && philo->meals_eaten >= philo->data->max_meals)
        return (true);
    return (false);
}
