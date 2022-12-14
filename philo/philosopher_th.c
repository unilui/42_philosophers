/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_th.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:22:41 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/23 15:40:16 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	put_message(t_philo *ph, char *message)
{
	pthread_mutex_lock(ph->print_mtx);
	printf("%zu: 😈 %d %s\n", current_time(ph->time_mtx), ph->id + 1, message);
	pthread_mutex_unlock(ph->print_mtx);
}

int	get_forks(t_philo *ph)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&ph->fork_mtx[(int)ph->left_fork]);
	pthread_mutex_lock(&ph->fork_mtx[(int)ph->right_fork]);
	if (ph->forks[(int)ph->left_fork] && ph->forks[(int)ph->right_fork]
		&& simulation_status(ph) == RUNNING)
	{
		ph->forks[(int)ph->left_fork] = 0;
		ph->forks[(int)ph->right_fork] = 0;
		put_message(ph, "has taken a fork 🥢");
		put_message(ph, "has taken a fork 🥢");
		status = 1;
		ph->holding_fork = 1;
	}
	else
	{
		pthread_mutex_unlock(&ph->fork_mtx[(int)ph->left_fork]);
		pthread_mutex_unlock(&ph->fork_mtx[(int)ph->right_fork]);
	}
	return (status);
}

void	return_forks(t_philo *ph)
{
	ph->forks[(int)ph->left_fork] = 1;
	ph->forks[(int)ph->right_fork] = 1;
	ph->holding_fork = 0;
	pthread_mutex_unlock(&ph->fork_mtx[(int)ph->left_fork]);
	pthread_mutex_unlock(&ph->fork_mtx[(int)ph->right_fork]);
}

void	call_waitress(t_philo *ph)
{
	pthread_mutex_lock(&ph->philo_mtx);
	ph->time_to_die = current_time(ph->time_mtx) + ph->ttd;
	ph->orders++;
	pthread_mutex_unlock(&ph->philo_mtx);
}

void	*philosopher(void *args)
{
	t_philo	*ph;

	ph = (t_philo *)args;
	if (ph->id % 2)
		usleep(5000);
	while (simulation_status(ph) == RUNNING)
	{
		thinking(ph);
		while (!get_forks(ph) && simulation_status(ph) == RUNNING)
			continue ;
		if (simulation_status(ph) == STOP)
			break ;
		eating(ph);
		if (simulation_status(ph) == STOP)
			break ;
		sleeping(ph);
	}
	if (ph->holding_fork)
		return_forks(ph);
	return (NULL);
}
