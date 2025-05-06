/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezghari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:03:39 by aezghari          #+#    #+#             */
/*   Updated: 2025/05/06 11:03:42 by aezghari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_fun(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (exceed_time_to_die(data))
			break ;
		if (all_eat_enough(data) == true)
			break ;
		usleep(500);
	}
	return (NULL);
}

static void	routine(t_philo *philo)
{
	while (!is_sim_end(philo->data))
	{
		if (p_eat(philo) == -1)
			break ;
		if (p_sleep(philo) == -1)
			break ;
		if (p_think(philo) == -1)
			break ;
	}
}

void	*philos(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		one_philo_case(philo);
		return (NULL);
	}
	if (philo->philo_id % 2)
		usleep(500);
	routine(philo);
	return (NULL);
}
