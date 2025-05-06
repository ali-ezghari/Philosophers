/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezghari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:37:05 by aezghari          #+#    #+#             */
/*   Updated: 2025/05/05 21:37:35 by aezghari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char const *argv[])
{
	struct s_data	*data;

	if (argc < 5 || argc > 6 || parsing(argv + 1) == -1)
		return (err());
	data = malloc(sizeof(t_data));
	if (!data)
		return (mem_err());
	if (data_init(data, argv + 1) == -1 || philo_init(data) == -1)
	{
		free(data);
		return (-1);
	}
	thread_init(data);
	destroy_free_all(data);
	return (0);
}
