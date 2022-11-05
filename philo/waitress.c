/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:22:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/04 21:35:41 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*waitress(void *args)
{
	int		id;
	t_data	*data;

	data = (t_data *)args;
	while (data->simulation == STOP)
		continue ;
	while (data->simulation == RUNNING)
	{
		id = 0;
		while (id < data->number_of_philosophers
			&& data->simulation == RUNNING)
		{
			if (data->ph[id].orders < data->philosopher_must_eat)
				id = 0;
			else
				id++;
		}
		pthread_mutex_lock(&data->simulation_mtx);
		data->simulation = STOP;
		pthread_mutex_unlock(&data->simulation_mtx);
	}
	return (NULL);
}
