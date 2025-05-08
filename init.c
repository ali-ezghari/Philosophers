/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezghari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:59:54 by aezghari          #+#    #+#             */
/*   Updated: 2025/05/06 10:59:55 by aezghari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init(t_data *data, char const *argv[])
{
	data->num_philos = ft_atoi(argv[0]);
	data->time_to_die = ft_atoi(argv[1]);
	data->time_to_eat = ft_atoi(argv[2]);
	data->time_to_sleep = ft_atoi(argv[3]);
	if (argv[4] && ft_atoi(argv[4]) > 0)
		data->max_meals = ft_atoi(argv[4]);
	else
		data->max_meals = -1;
	data->philo = malloc(sizeof(t_philo) * data->num_philos);
	if (data->philo == NULL)
		return (mem_err());
	data->sim_end = false;
	data->full_philos = 0;
	gettimeofday(&data->start_time, NULL);
	if (pthread_mutex_init(&(data->meals_lock), NULL) != 0)
		return (destroy_free(data, 1337),
			mutex_destroy_err());
	if (pthread_mutex_init(&(data->write_lock), NULL) != 0)
		return (destroy_free(data, 1),
			mutex_destroy_err());
	if (pthread_mutex_init(&(data->death_lock), NULL) != 0)
		return (destroy_free(data, 2),
			mutex_destroy_err());
	return (0);
}

int	philo_init(t_data *data)
{
	int	i;

	i = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (mem_err());
	while (++i < data->num_philos)
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (clean_forks_array(data, i), mutex_init_err());
	i = -1;
	while (++i < data->num_philos)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].data = data;
		data->philo[i].last_time_eat = get_time_in__ms();
		data->philo[i].right_fork = &data->forks[i];
		if (data->num_philos == 1)
			data->philo[i].left_fork = NULL;
		else
			data->philo[i].left_fork = &data->forks[(i + 1) % data->num_philos];
	}
	return (0);
}

int	thread_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->philo[i].p_thread, NULL, philos,
				&data->philo[i]) != 0)
		{
			join_philo_threads(data, i);
			return (thread_err(data));
		}
	}
	if (pthread_create(&data->monitor, NULL, monitor_fun, data) != 0)
	{
		join_philo_threads(data, i);
		return (thread_err(data));
	}
	i = -1;
	while (++i < data->num_philos)
		if (pthread_join(data->philo[i].p_thread, NULL) != 0)
			return (thread_err(data));
	if (pthread_join(data->monitor, NULL) != 0)
		return (thread_err(data));
	return (0);
}
