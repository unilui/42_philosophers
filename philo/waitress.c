/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:22:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/22 22:21:57 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*waitress(void *args)
{
	int		id;
	int		actual;
	t_data	*data;

	data = (t_data *)args;
	while (data->simulation == RUNNING)
	{
		id = 0;
		while (id < data->number_of_philosophers
			&& simulation_status(&data->ph[id]) == RUNNING)
		{
			actual = id;
			pthread_mutex_lock(&data->ph[actual].philo_mtx);
			if (data->ph[id].orders < data->philosopher_must_eat)
				id = 0;
			else
				id++;
			pthread_mutex_unlock(&data->ph[actual].philo_mtx);
			usleep(20);
		}
		usleep(500);
		pthread_mutex_lock(&data->simulation_mtx);
		data->simulation = STOP;
		pthread_mutex_unlock(&data->simulation_mtx);
	}
	return (NULL);
}
