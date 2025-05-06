/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezghari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:58:32 by aezghari          #+#    #+#             */
/*   Updated: 2025/05/06 10:58:50 by aezghari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in__ms(void)
{
	struct timeval	curr_time;
	long			now;

	gettimeofday(&curr_time, NULL);
	now = (curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000);
	return (now);
}

long	get_elapsed_time(t_philo *philo)
{
	struct timeval	curr_time;
	long			elapsed_ms;

	gettimeofday(&curr_time, NULL);
	elapsed_ms = (curr_time.tv_sec - philo->data->start_time.tv_sec) * 1000
		+ (curr_time.tv_usec - philo->data->start_time.tv_usec) / 1000;
	return (elapsed_ms);
}

void	print_state(t_philo *philo, char *msg)
{
	if (!is_sim_end(philo->data))
	{
		pthread_mutex_lock(&philo->data->write_lock);
		printf("%ld %d %s\n", get_elapsed_time(philo), philo->philo_id, msg);
		pthread_mutex_unlock(&philo->data->write_lock);
	}
}

void	one_philo_case(t_philo *philo)
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

void	join_philo_threads(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_join(data->philo[i].p_thread, NULL) != 0)
			printf("Failed to join thread %d\n", i);
		i++;
	}
}
