/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezghari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:04:17 by aezghari          #+#    #+#             */
/*   Updated: 2025/05/06 11:04:52 by aezghari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	exceed_time_to_die(t_data *data)
{
	int		i;
	long	last_time_eat;

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

bool	all_eat_enough(t_data *data)
{
	int	full_philos;

	if (is_sim_end(data))
		return (true);
	pthread_mutex_lock(&data->meals_lock);
	full_philos = data->full_philos;
	pthread_mutex_unlock(&data->meals_lock);
	if (full_philos == data->num_philos)
	{
		pthread_mutex_lock(&data->death_lock);
		data->sim_end = 1;
		pthread_mutex_unlock(&data->death_lock);
		return (true);
	}
	return (false);
}

void	ft_sleep(long mill)
{
	long	start;

	start = get_time_in__ms();
	while ((get_time_in__ms() - start) < mill)
	{
		usleep(200);
	}
}

int	is_sim_end(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_lock);
	result = data->sim_end;
	pthread_mutex_unlock(&data->death_lock);
	return (result);
}

int	check_number_meals(t_philo *philo)
{
	if (philo->data->max_meals == -1)
		return (0);
	pthread_mutex_lock(&philo->data->meals_lock);
	if (philo->meals_eaten == philo->data->max_meals)
	{
		philo->data->full_philos++;
		pthread_mutex_unlock(&philo->data->meals_lock);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->meals_lock);
	return (0);
}
