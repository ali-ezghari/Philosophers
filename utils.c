#include "philo.h"

long get_time_in__ms(void)
{
	struct timeval curr_time;
	long now;

	gettimeofday(&curr_time, NULL);
	now = (curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000);
	return (now);
}

long get_elapsed_time(t_philo *philo)
{
	struct timeval curr_time;
	long elapsed_ms;

	gettimeofday(&curr_time, NULL);
	elapsed_ms = (curr_time.tv_sec - philo->data->start_time.tv_sec) * 1000 + (curr_time.tv_usec - philo->data->start_time.tv_usec) / 1000; // calculating the time that goes by since the simulation started
	return (elapsed_ms);
}

void print_state(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->write_lock); // lock the mutex to avoid multiple threads writing at the same time
	printf("%ld %d %s\n", get_elapsed_time(philo), philo->philo_id, msg);
	pthread_mutex_unlock(&philo->data->write_lock);
}

int is_sim_end(t_data *data)
{
	int result;

	pthread_mutex_lock(&data->death_lock);
	result = data->sim_end;
	pthread_mutex_unlock(&data->death_lock);
	return (result);
}

void one_philo_case(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    print_state(philo, "has taken a fork");
    pthread_mutex_unlock(philo->right_fork);
    usleep(philo->data->time_to_die * 1000);
    print_state(philo, "died");
    pthread_mutex_lock(&philo->data->death_lock);
    philo->data->sim_end = true;
    pthread_mutex_unlock(&philo->data->death_lock);
}
