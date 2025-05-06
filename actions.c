#include "philo.h"

int p_eat(t_philo *philo)
{
    if (philo->philo_id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken a fork");
    }
    print_state(philo, "is eating");
    pthread_mutex_lock(&philo->data->meals_lock);
    philo->meals_eaten++;
    philo->last_time_eat = get_time_in__ms();
    pthread_mutex_unlock(&philo->data->meals_lock);
    ft_sleep(philo->data->time_to_eat);
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
    ft_sleep(philo->data->time_to_sleep);
    return (0);
}

int p_think(t_philo *philo)
{
    int think_time;

    if (is_sim_end(philo->data))
        return (-1);
    think_time = (philo->data->time_to_die / 2) - philo->data->time_to_eat;
    if (think_time < 5)
        think_time = 5;
    if (think_time > 100)
        think_time = 100;
    print_state(philo, "is thinking");
    ft_sleep(think_time);
    return (0);
}