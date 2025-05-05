#include "philo.h"

static int check_number_meals(t_philo *philo)
{
    int times_eat;

    if (philo->data->max_meals == -1)
        return (0);
    pthread_mutex_lock(&philo->data->meals_lock);
    times_eat = philo->meals_eaten;
    pthread_mutex_unlock(&philo->data->meals_lock);
    if (philo->meals_eaten == times_eat)
    {
        pthread_mutex_lock(&philo->data->meals_lock);
        philo->data->full_philos++;
        pthread_mutex_unlock(&philo->data->meals_lock);
        return (-1);
    }
    return (0);
}

int p_eat(t_philo *philo)
{
    if (is_sim_end(philo->data))
        return (-1);
    pthread_mutex_lock(philo->right_fork);
    print_state(philo, "has taken a fork");
    pthread_mutex_lock(philo->left_fork);
    print_state(philo, "has taken a fork");
    print_state(philo, "is eating");
    pthread_mutex_lock(&philo->data->meals_lock);
    philo->meals_eaten++;
    philo->last_time_eat = get_time_in__ms();
    pthread_mutex_unlock(&philo->data->meals_lock);
    ft_sleep(philo->data->time_to_eat, philo->data);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    if (check_number_meals(philo) == -1 || is_sim_end(philo->data))
        return (-1);
    return (0);
}
int p_sleep(t_philo *philo)
{
    if (is_sim_end(philo->data))
        return (-1);
    print_state(philo, "is sleeping");
    ft_sleep(philo->data->time_to_sleep, philo->data);
    return (0);
}

int p_think(t_philo *philo)
{
    if (is_sim_end(philo->data))
        return (-1);
    print_state(philo, "is thinking");
    return (0);
}