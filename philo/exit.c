/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:22:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/22 22:13:59 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_memory(t_data *data)
{
	free(data->th);
	free(data->ph);
	free(data->forks);
	free(data->fork_mtx);
}

void	destroy_mtx(t_data *data)
{
	int	id;
	int	nbr;

	id = 0;
	nbr = data->number_of_philosophers;
	pthread_mutex_destroy(&data->simulation_mtx);
	pthread_mutex_destroy(&data->print_mtx);
	pthread_mutex_destroy(&data->time_mtx);
	while (id < nbr)
	{
		pthread_mutex_destroy(&data->ph[id].philo_mtx);
		id ++;
	}
	id = 0;
	while (id < (nbr + (nbr == 1)))
	{
		pthread_mutex_destroy(&data->fork_mtx[id]);
		id ++;
	}
}

void	wait_threads(t_data *data)
{
	int	id;

	id = 0;
	pthread_join(data->cm, NULL);
	if (data->philosopher_must_eat)
		pthread_join(data->wt, NULL);
	while (id < data->number_of_philosophers)
	{
		pthread_join(data->th[id], NULL);
		id++;
	}
}
