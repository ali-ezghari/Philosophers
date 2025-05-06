/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezghari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:59:07 by aezghari          #+#    #+#             */
/*   Updated: 2025/05/06 10:59:43 by aezghari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mem_err(void)
{
	printf("Memory allocation failed\n");
	return (-1);
}

int	err(void)
{
	printf("Error\n");
	return (-1);
}

int	mutex_init_err(void)
{
	printf("error occured while initializing the mutex\n");
	return (-1);
}

int	mutex_destroy_err(void)
{
	printf("error occured while destroying the mutex\n");
	return (-1);
}

int	thread_err(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	data->sim_end = true;
	pthread_mutex_unlock(&data->death_lock);
	printf("Error occured while creating or joining threads\n");
	return (-1);
}
