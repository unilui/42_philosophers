/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:22:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/06 17:49:13 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_simulation(int argc, char **argv, t_data *data)
{
	memset(data, 0, sizeof(t_data));
	data->simulation = RUNNING;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->philosopher_must_eat = 0;
	data->ph = ft_calloc(data->number_of_philosophers, sizeof(t_philo));
	data->th = ft_calloc(data->number_of_philosophers, sizeof(pthread_t));
	data->forks = ft_calloc((data->number_of_philosophers
				+ (data->number_of_philosophers == 1)),
			sizeof(char));
	data->fork_mtx = ft_calloc((data->number_of_philosophers
				+ (data->number_of_philosophers == 1)),
			sizeof(pthread_mutex_t));
	if (!data->ph || !data->th || !data->forks || !data->fork_mtx)
		return (0);
	return (1);
}

void	create_threads(t_data *data)
{
	int	id;

	id = 0;
	while (id < data->number_of_philosophers)
	{
		pthread_create(&data->th[id],
			NULL, &philosopher, (void *)&data->ph[id]);
		id++;
	}
	if (data->philosopher_must_eat)
		pthread_create(&data->wt, NULL, &waitress, (void *)data);
	pthread_create(&data->cm, NULL, &cardiac_monitor, (void *)data);
}

void	init_philosophers(t_data *data)
{
	int	id;
	int	nbr;

	id = 0;
	nbr = data->number_of_philosophers;
	while (id < nbr)
	{
		data->ph[id].simulation = &data->simulation;
		data->ph[id].simulation_mtx = &data->simulation_mtx;
		data->ph[id].time_to_die = data->time_to_die;
		data->ph[id].ttd = data->time_to_die;
		data->ph[id].time_to_eat = data->time_to_eat;
		data->ph[id].time_to_sleep = data->time_to_sleep;
		data->ph[id].forks = data->forks;
		data->ph[id].fork_mtx = data->fork_mtx;
		data->ph[id].left_fork = id;
		if (id == (nbr - 1) && nbr > 1)
			data->ph[id].right_fork = 0;
		else
			data->ph[id].right_fork = id + 1;
		data->ph[id].id = id;
		id++;
	}
}

void	init_mtx(t_data *data)
{
	int	id;
	int	nbr;

	id = 0;
	nbr = data->number_of_philosophers;
	pthread_mutex_init(&data->simulation_mtx, NULL);
	while (id < nbr)
	{
		pthread_mutex_init(&data->ph[id].philo_mtx, NULL);
		id ++;
	}
	id = 0;
	while (id < (nbr + (nbr == 1)))
	{
		pthread_mutex_init(&data->fork_mtx[id], NULL);
		id ++;
	}
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->forks[i] = 1;
		i++;
	}
}
