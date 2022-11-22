/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardiac_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:22:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/22 22:12:12 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*cardiac_monitor(void *args)
{
	int		id;
	t_data	*data;

	id = 0;
	data = (t_data *)args;
	while (id < data->number_of_philosophers
		&& data->simulation == RUNNING)
	{
		pthread_mutex_lock(&data->simulation_mtx);
		pthread_mutex_lock(&data->ph[id].philo_mtx);
		if ((int)current_time() > data->ph[id].time_to_die)
		{
			data->simulation = STOP;
			pthread_mutex_lock(&data->print_mtx);
			printf("%zu: 😵 %d died 💀\n", current_time(), id + 1);
			pthread_mutex_unlock(&data->print_mtx);
		}
		pthread_mutex_unlock(&data->simulation_mtx);
		pthread_mutex_unlock(&data->ph[id].philo_mtx);
		id++;
		if (id == data->number_of_philosophers)
			id = 0;
		usleep(20);
	}
	return (NULL);
}
