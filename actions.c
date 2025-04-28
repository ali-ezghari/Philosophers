#include "philo.h"
static int print_taking_fork1(t_philo *philo)
{
    if (is_sim_end(philo->data))
    {
        return (-1);
    }
    print_state(philo, "has taken a fork");
    return (0);
}
static int print_taking_fork2(t_philo *philo)
{
    if (is_sim_end(philo->data))
    {
        return (-1);
    }
    print_state(philo, "has taken a fork");
    print_state(philo, "is eating");
    return (0);
}
static void number_of_meals_counter(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->write_lock);
    if (philo->meals_eaten < philo->data->max_meals)
        philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->write_lock);
}
static int check_number_meals(t_philo *philo)
{
    int times_eat;

    pthread_mutex_lock(&philo->data->write_lock);
    times_eat = philo->data->max_meals;
    pthread_mutex_unlock(&philo->data->write_lock);
    if (philo->meals_eaten == times_eat)
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        return (-1);
    }
    return (0);
}
int p_eat(t_philo *philo)
{
    if (is_sim_end(philo->data))
    {
        return (-1);
    }
    pthread_mutex_lock(philo->right_fork);
    if (print_taking_fork1(philo) == -1)
    {
        pthread_mutex_unlock(philo->right_fork);
        return (-1);
    }
    pthread_mutex_lock(philo->left_fork);
    if (print_taking_fork2(philo) == -1)
    {
        pthread_mutex_unlock(philo->right_fork);
        return (-1);
    }
    pthread_mutex_lock(&philo->data->death_lock);
    philo->last_time_eat = get_time_in__ms();
    pthread_mutex_unlock(&philo->data->death_lock);
    print_state(philo, "is eating");
    ft_sleep(philo->data->time_to_eat * 1000);
    number_of_meals_counter(philo);
    if (check_number_meals(philo) == -1)
        return (-1);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    return (0);
}
int p_sleep(t_philo *philo)
{
    if (is_sim_end(philo->data))
        return (-1);
    print_state(philo, "is sleeping");
    ft_sleep(philo->data->time_to_sleep * 1000);
    return (0);
}

int p_think(t_philo *philo)
{
    long think_time;

    if (is_sim_end(philo->data))
        return (-1);
    print_state(philo, "is thinking");
    ft_sleep(think_time);
    return (0);
}
