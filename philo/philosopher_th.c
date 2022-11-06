/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_th.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:22:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/06 17:38:52 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	simulation_status(t_philo *ph)
{
	int	status;

	pthread_mutex_lock(ph->simulation_mtx);
	status = *ph->simulation;
	pthread_mutex_unlock(ph->simulation_mtx);
	return (status);
}

int	get_forks(t_philo *ph)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&ph->fork_mtx[ph->left_fork]);
	pthread_mutex_lock(&ph->fork_mtx[ph->right_fork]);
	if (ph->forks[ph->left_fork] && ph->forks[ph->right_fork]
		&& *ph->simulation == RUNNING)
	{
		ph->forks[ph->left_fork] = 0;
		ph->forks[ph->right_fork] = 0;
		printf("%zu: 😈 %d has taken a fork 🥢\n",
			current_time(), ph->id + 1);
		printf("%zu: 😈 %d has taken a fork 🥢\n",
			current_time(), ph->id + 1);
		status = 1;
	}
	else
	{
		pthread_mutex_unlock(&ph->fork_mtx[ph->left_fork]);
		pthread_mutex_unlock(&ph->fork_mtx[ph->right_fork]);
	}
	return (status);
}

void	return_forks(t_philo *ph)
{
	ph->forks[ph->left_fork] = 1;
	ph->forks[ph->right_fork] = 1;
	pthread_mutex_unlock(&ph->fork_mtx[ph->left_fork]);
	pthread_mutex_unlock(&ph->fork_mtx[ph->right_fork]);
}

void	call_waitress(t_philo *ph)
{
	pthread_mutex_lock(&ph->philo_mtx);
	ph->time_to_die = current_time() + ph->ttd;
	ph->orders++;
	pthread_mutex_unlock(&ph->philo_mtx);
}

void	*philosopher(void *args)
{
	t_philo	*info;

	info = (t_philo *)args;
	if (info->id % 2)
		usleep(5000);
	while (simulation_status(info) == RUNNING)
	{
		printf("%zu: 😈 %d is thinking 🤔\n", current_time(), info->id + 1);
		while (!get_forks(info) && simulation_status(info) == RUNNING)
			continue ;
		if (simulation_status(info) == STOP)
		{
			return_forks(info);
			break ;
		}
		printf("%zu: 😈 %d is eating 🍽️\n", current_time(), info->id + 1);
		usleep(info->time_to_eat * 1000);
		call_waitress(info);
		return_forks(info);
		if (simulation_status(info) == STOP)
			break ;
		printf("%zu: 😈 %d is sleeping 😴\n", current_time(), info->id + 1);
		usleep(info->time_to_sleep * 1000);
	}
	return (NULL);
}
